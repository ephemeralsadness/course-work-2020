#pragma once

#include <utility>
#include <algorithm>

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
		this->~Vector();
		_size = v._size;
		_capacity = v._capacity;
		_data = v._data;
		v._size = 0;
		v._capacity = 0;
		v._data = nullptr;

		return *this;
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
		}
		else {
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

	void Erase(size_t index) {
		for (size_t i = index; i < _size - 1; ++i) {
			_data[i] = std::move(_data[i + 1]);
		}
		_data[--_size];
	}

	void Reserve(size_t capacity) noexcept {
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

	template <typename Comp>
	void MergeSort(Comp comp) noexcept {
		auto begin = Begin();
		auto end = End();

		if (end - begin <= 1) return;

		T* mid = begin + (end - begin) / 2;

		Vector<T> left;
		left.Reserve(mid - left);
		for (auto it = begin; it != mid; ++it)
			left.PushBack(*it);

		Vector<T> right;
		right.Reserve(end - mid);
		for (auto it = mid; it != end; ++it)
			right.PushBack(*it);

		left.MergeSort(comp);
		right.MergeSort(comp);
		Merge(left, right, comp);
	}

	template <typename ToFind, typename Comp>
	size_t BinarySearch(T& to_find, Comp comp) {
		auto left = Begin();
		auto right = End();
		while (left < right) {
			auto mid = left + (right - left) / 2;
			bool is_lower = comp(*mid, to_find);
			bool is_greater = comp(to_find, *mid);

			if (is_lower && is_greater) {
				return mid - left;
			}
			else if (is_lower) {
				left = mid + 1;
			}
			else {
				right = mid;
			}
		}

		return -1;
	}

private:

	template <typename Comp>
	void Merge(Vector<T>& left, Vector<T>& right, Comp comp) {
		auto l_ptr = left.Begin();
		auto r_ptr = right.Begin();
		auto out_ptr = Begin();

		while (l_ptr != left.End() && r_ptr != right.End()) {
			if (comp(*l_ptr, *r_ptr)) {
				*out_ptr = *l_ptr;
				++l_ptr;
			}
			else {
				*out_ptr = *r_ptr;
				++r_ptr;
			}
			++out_ptr;
		}

		while (l_ptr != left.End()) {
			*out_ptr = *l_ptr;
			++l_ptr;
			++out_ptr;
		}

		while (r_ptr != right.End()) {
			*out_ptr = *r_ptr;
			++r_ptr;
			++out_ptr;
		}
	}


	size_t _size;
	size_t _capacity;
	T* _data;
};

