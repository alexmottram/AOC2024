//
// Created by Alexander Mottram on 29/04/2024.
//
#pragma once

#include "precompile_header.h"
#include "vector_tools.h"

namespace utils {
    template<typename T>
    class Array2D;

    // Forward assign Array operators
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Array2D<T>& a);

    template<class T>
    struct Row {
        // Iterator tags here...

        // Iterator constructors here...
        Row(T* ptr, size_t row_size)
                :m_ptr(ptr), row_size(row_size)
        {
            row_start = ptr;
        }

        Row(T* ptr, const T* row_start, size_t row_size)
                :m_ptr(ptr), row_start(row_start), row_size(row_size) { }

        T& operator*() const { return *m_ptr; }

        T* operator->() { return m_ptr; }

        // Prefix increment
        T& operator++()
        {
            m_ptr++;
            return *m_ptr;
        }

        // Postfix increment
        T operator++(int)
        {
            T tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Row& a, const Row& b)
        {
            return a.m_ptr==b.m_ptr;
        };

        friend bool operator!=(const Row& a, const Row& b)
        {
            return a.m_ptr!=b.m_ptr;
        };

        auto row_end() { return row_start+row_size; }

        auto begin() { return Row<T>(m_ptr, row_start, row_size); }

        auto end() { return Row<T>(m_ptr, row_end(), row_size); }

        auto begin() const { return Row<T>(m_ptr, row_start, row_size); }

        auto end() const { return Row<T>(m_ptr, row_end(), row_size); }

    private:
        T* m_ptr;
        const T* row_start;
        const size_t row_size;
    };

    template<class T>
    struct RowIterator {
        // Iterator tags here...

        // Iterator constructors here...
        RowIterator(T* ptr, std::vector<T>* vector_ptr, size_t row_size)
                :m_ptr(ptr), m_vector_ptr(vector_ptr), row_size(row_size) { }

        // Iterator constructors here...
        RowIterator(std::vector<T>* vector_ptr, size_t row_size)
                :m_vector_ptr(vector_ptr), row_size(row_size)
        {
            m_ptr = &(*m_vector_ptr->begin());
        }

        Row<T> operator*() const { return Row<T>{m_ptr, row_size}; }

        Row<T>* operator->() { return Row<T>{m_ptr, row_size}; }

        // Prefix increment
        Row<T> operator++()
        {
            m_ptr += row_size;
            return Row<T>{m_ptr, row_size};
        }

        // Postfix increment
        Row<T> operator++(int)
        {
            Row<T> tmp = Row<T>{m_ptr, row_size};
            (*this) += row_size;
            return tmp;
        }

        friend bool operator==(const RowIterator& a, const RowIterator& b)
        {
            return a.m_ptr==b.m_ptr;
        };

        friend bool operator!=(const RowIterator& a, const RowIterator& b)
        {
            return a.m_ptr!=b.m_ptr;
        };

        auto row_iterator_begin()
        {
            return &(*m_vector_ptr->begin());
        }

        auto row_iterator_end()
        {
            return &(*m_vector_ptr->end());
        }

        auto begin()
        {
            return RowIterator<T>(row_iterator_begin(), m_vector_ptr, row_size);
        }

        auto end()
        {
            return RowIterator<T>(row_iterator_end(), m_vector_ptr, row_size);
        }

        auto begin() const
        {
            return RowIterator<T>(row_iterator_begin(), m_vector_ptr, row_size);
        }

        auto end() const
        {
            return RowIterator<T>(row_iterator_end(), m_vector_ptr, row_size);
        }

    private:
        T* m_ptr;
        std::vector<T>* m_vector_ptr;
        const size_t row_size;
    };
}