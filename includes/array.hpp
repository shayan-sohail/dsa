#ifndef ARRAY_H
#define ARRAY_H

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>

template <class T, size_t Size>
class Array
{
private:
    const size_t m_size;

public:
    T* data;
    Array() noexcept : m_size(Size) { data = new T[m_size]; }

    Array(T t) noexcept : m_size(Size)
    {
        data = new T[m_size];
        fill(t);
    }

    Array(std::initializer_list<T> init_list) noexcept : m_size(Size)
    {
        data = new T[m_size];
        auto it = init_list.begin();

        for (size_t i = 0; i < Size && it != init_list.end(); i++, ++it)
            data[i] = *it;

        if (init_list.size() < m_size)
            std::fill(data + init_list.size(), data + m_size, T());
    }

    ~Array() noexcept { delete[] data; }

    void fill(const T& value) noexcept
    {
        for (size_t i = 0; i < Size; i++)
        {
            data[i] = value;
        }
    }

    size_t size() const noexcept { return m_size; }

    T at(size_t index) const
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of bound");
        }
        return (*this)[index];
    }

    T& operator[](size_t index)
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of bound");
        }
        return data[index];
    }

    const T& operator[](size_t index) const noexcept
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of bound");
        }
        return data[index];
    }

    // Iterator typedefs
    typedef T* iterator;
    typedef const T* const_iterator;

    // Iterator functions
    iterator begin() noexcept { return data; }
    iterator end() noexcept { return data + m_size; }
    const_iterator begin() const noexcept { return data; }
    const_iterator end() const noexcept { return data + m_size; }
    const_iterator cbegin() const noexcept { return data; }
    const_iterator cend() const noexcept { return data + m_size; }

    friend std::ostream& operator<<(std::ostream& os, const Array<T, Size>& obj) noexcept
    {
        os << "Array<" << obj.size() << ">";
        return os;
    }
};

#endif // ARRAY_H