#pragma once

#include <utility>

template <typename T>
class Vector {
    Vector() noexcept;
    ~Vector() noexcept;
    Vector(const Vector<T>& v) noexcept;
    Vector<T>& operator = (const Vector<T>& v) noexcept;
    Vector(Vector<T>&& v) noexcept;
    Vector<T>& operator = (Vector<T>&& v) noexcept;

    T& operator [] (size_t index) noexcept;
    const T& operator [] (size_t index) const noexcept;

    void PushBack(T t) noexcept;
    void PopBack() noexcept;

    void Reserve() noexcept;

    T* Begin() noexcept;
    const T* Begin() const noexcept;
    T* End() noexcept;
    const T* End() const noexcept;

    size_t Size() const noexcept;
};