#pragma once

#include <utility>

template <typename T>
class Vector {
public:
    Vector() noexcept
            : _size(0),
              _capacity(0),
              _data(nullptr) {}

    ~Vector() noexcept {
        delete[] _data;
    }

    Vector(const Vector<T>& v) noexcept
            : _size(v._size),
              _capacity(v._size),
              _data(nullptr) {
        if (v._size == 0) return;

        _data = new T[_capacity];
        for (int i = 0; i < _size; ++i)
            _data[i] = v._data[i];
    }

    Vector<T>& operator = (const Vector<T>& v) noexcept {
        if (this == &v) return *this;
        *this = std::move(Vector(v));
        return *this;
    }

    Vector(Vector<T>&& v) noexcept
            : _size(v._size),
              _capacity(v._capacity),
              _data(v._data) {
        v._size = 0;
        v._capacity = 0;
        v._data = nullptr;
    }

    Vector<T>& operator = (Vector<T>&& v) noexcept {
        ~Vector();
        _size = v._size;
        _capacity = v._capacity;
        _data = v._data;
        v._size = 0;
        v._capacity = 0;
        v._data = nullptr;
    }

    T& operator [] (size_t index) noexcept {
        return _data[index];
    }

    const T& operator [] (size_t index) const noexcept {
        return _data[index];
    }

    void PushBack(T t) noexcept {
        if (_size < _capacity) {
            _data[_size++] = std::move(t);
        } else {
            _capacity = (_capacity == 0 ? 1 : _capacity * 2);
            T* prev_data = _data;
            _data = new T[_capacity];

            _data[_size] = std::move(t);

            for (int i = 0; i < _size; ++i)
                _data[i] = std::move(prev_data[i]);

            _size++;
            delete[] prev_data;
        }
    }

    void PopBack() noexcept {
        _data[--_size].~T();
    }

    void Reserve(int capacity) noexcept {
        if (capacity <= _capacity)
            return;

        _capacity = capacity;
        T* prev_data = _data;
        _data = new T[_capacity];

        for (int i = 0; i < _size; ++i)
            _data[i] = prev_data[i];

        delete[] prev_data;
    }

    T* Begin() noexcept {
        return _data;
    }
    const T* Begin() const noexcept {
        return _data;
    }
    T* End() noexcept {
        return _data + _size;
    }
    const T* End() const noexcept {
        return _data + _size;
    }

    size_t Size() const noexcept {
        return _size;
    }

private:
    size_t _size;
    size_t _capacity;
    T* _data;
};