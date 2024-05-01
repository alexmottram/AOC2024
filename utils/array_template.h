//
// Created by Alexander Mottram on 04/12/2023.
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

//    template<class T>
//    class Row {
//    public:
//        Array2D<T>* array_ref{};
//        size_t row_num{};
//
//        explicit Row(Array2D<T>* array_ref);
//
//        size_t size()
//        {
//            return array_ref->get_size_x();
//        }
//
//        // Standard vector based begin and ends
//        auto begin()
//        {
//            return array_ref->data.begin()+(row_num*size());
//        }
//
//        auto end()
//        {
//            return array_ref->data.begin()+((row_num+1)*size());
//        }
//
//        auto begin() const
//        {
//            return array_ref->data.begin()+(row_num+*size());
//        }
//
//        auto end() const
//        {
//            return array_ref->data.begin()+ +((row_num+1)*size());
//        }
//
//    };
//
//    template<class T>
//    Row<T>::Row(Array2D<T>* array_ref)
//    {
//        this->array_ref = array_ref;
//        this->row_num = 1;
//
//    }


    template<class T>
    struct Row {
        // Iterator tags here...

        // Iterator constructors here...
        Row(T* ptr, Array2D<T>* array_ptr)
                :m_ptr(ptr), m_array_ptr(array_ptr) { }

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

        auto row_start()
        {
            return m_ptr;
        }

        auto row_end()
        {
            return row_start()+(m_array_ptr->get_size_x());
        }

        auto begin()
        {
            return Row<T>(row_start(), m_array_ptr);
        }

        auto end()
        {
            return Row<T>(row_end(), m_array_ptr);
        }

        auto begin() const
        {
            return Row<T>(row_start(), m_array_ptr);
        }

        auto end() const
        {
            return Row<T>(row_end(), m_array_ptr);
        }

    private:
        Array2D<T>* m_array_ptr;
        T* m_ptr;
    };

    template<class T>
    struct RowIterator {
        // Iterator tags here...

        // Iterator constructors here...
        RowIterator(T* ptr, Array2D<T>* array_ptr)
                :m_ptr(ptr), m_array_ptr(array_ptr) { }

        Row<T> operator*() const { return Row<T>{m_ptr, m_array_ptr}; }

        Row<T>* operator->() { return Row<T>{m_ptr, m_array_ptr}; }

        // Prefix increment
        Row<T> operator++()
        {
            m_ptr += m_array_ptr->get_size_x();
            return Row<T>{m_ptr, m_array_ptr};
        }

        // Postfix increment
        Row<T> operator++(int)
        {
            Row<T> tmp = Row<T>{m_ptr, m_array_ptr};
            (*this) += m_array_ptr->get_size_x();
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
            return &(*m_array_ptr->begin());
        }

        auto row_iterator_end()
        {
            return &(*m_array_ptr->end());
        }

        auto begin()
        {
            return RowIterator<T>(row_iterator_begin(), m_array_ptr);
        }

        auto end()
        {
            return RowIterator<T>(row_iterator_end(), m_array_ptr);
        }

        auto begin() const
        {
            return RowIterator<T>(row_iterator_begin(), m_array_ptr);
        }

        auto end() const
        {
            return RowIterator<T>(row_iterator_end(), m_array_ptr);
        }

    private:
        Array2D<T>* m_array_ptr;
        T* m_ptr;
    };

    template<class T>
    class Array2D {
    public:
        using VecType = std::vector<T>;
        using DualVecType = std::vector<VecType>;

        explicit Array2D(const DualVecType& input_data);

        template<typename IdxT>
        T& at(IdxT x, IdxT y)
        {
            auto x_long = static_cast<long long> (x);
            auto y_long = static_cast<long long> (y);
            return at_cardinal(x_cardinal(x_long), y_cardinal(y_long));
        }

        T& at(Vec2D vec)
        {
            return at(vec.x, vec.y);
        }

        [[nodiscard]] size_t index_to_x_cardinal(size_t index) const
        {
            return index%size_y;
        }

        [[nodiscard]] long long index_to_actual_x(size_t index) const
        {
            return index_to_x_cardinal(index)+x_origin;
        }

        [[nodiscard]] size_t index_to_y_cardinal(size_t index) const
        {
            return index/size_y;
        }

        [[nodiscard]] long long index_to_actual_y(size_t index) const
        {
            return index_to_y_cardinal(index)+y_origin;
        }

        [[nodiscard]] size_t size() const
        {
            return this->data.size();
        }

        [[nodiscard]] size_t get_size_x() const
        {
            return size_x;
        }

        [[nodiscard]] size_t get_size_y() const
        {
            return size_y;
        }

        friend bool operator<(Array2D<T> const& lhs, Array2D<T> const& rhs)
        {
            return (
                    (lhs.size()<rhs.size())
                            || ((lhs.size()==rhs.size()) && (lhs.data<rhs.data))
            );
        }

        friend bool operator==(Array2D<T> const& lhs, Array2D<T> const& rhs)
        {
            return (lhs.get_size_x()==rhs.get_size_x())
                    && (lhs.get_size_y()==rhs.get_size_y())
                    && (lhs.data==rhs.data);
        }

        friend std::ostream& operator
        <<<T>(
        std::ostream& os,
        const Array2D<T>& a
        );

        // Standard vector based begin and ends
        auto begin()
        {
            return data.begin();
        }

        auto end()
        {
            return data.end();
        }

        auto begin() const
        {
            return data.begin();
        }

        auto end() const
        {
            return data.end();
        }

        // Row iterator
        RowIterator<T> row_iter();

    private:
        VecType data{};
        size_t size_x{};
        size_t size_y{};
        long long x_origin{0};
        long long y_origin{0};

        size_t x_cardinal(long long x);

        size_t y_cardinal(long long y);

        T& at_cardinal(const size_t& x_cardinal, const size_t& y_cardinal)
        {
            return data.at(cardinal_to_index(x_cardinal, y_cardinal));
        }

        size_t cardinal_to_index(const size_t& x_cardinal, const size_t& y_cardinal)
        {
            return (y_cardinal*size_x)+x_cardinal;
        }

    };

    template<class T>
    RowIterator<T> Array2D<T>::row_iter()
    {
        return RowIterator<T>{&data[0], this};
    }

    template<class T>
    Array2D<T>::Array2D(const DualVecType& input_data)
    {
        this->size_y = input_data.size();
        this->size_x = input_data.front().size();
        for (const auto& row : input_data) {
            if (row.size()!=this->size_x) {
                throw std::invalid_argument("Uneven subvector sizes.");
            }
            for (auto val : row) {
                this->data.push_back(val);
            }
        }
    }

    template<class T>
    size_t Array2D<T>::y_cardinal(long long int y)
    {
        long long y_card = y-y_origin;
        if (y_card>=0 && y_card<size_y) {
            return y_card;
        }
        else {
            throw std::invalid_argument("Y value outside of range");
        }
    }

    template<class T>
    size_t Array2D<T>::x_cardinal(long long int x)
    {
        long long x_card = x-x_origin;
        if (x_card>=0 && x_card<size_x) {
            return x_card;
        }
        else {
            throw std::invalid_argument("X value outside of range");
        }
    }

    template<class T>
    std::ostream& operator<<(std::ostream& os, const Array2D<T>& a)
    {
        for (auto i{0}; i<a.data.size(); i++) {
            // Pre value insert
            if (i%a.size_x==0) {
                os << "[";
            }
            // Value insert
            os << a.data.at(i);

            // Post value insert
            if ((i+1)%a.size_x==0) {
                os << "]\n";
            }
            else {
                os << ",";
            }
        }

        return os;
    }

}