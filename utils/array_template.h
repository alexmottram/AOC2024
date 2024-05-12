//
// Created by Alexander Mottram on 04/12/2023.
//
#pragma once

#include "precompile_header.h"
#include "vector_3d.h"
#include "array_utils.h"
#include "array_iterators.h"

namespace utils {
    template<typename T>
    class Array2D;

    template<typename T>
    class NodeWrapper;

    // Forward assign Array operators
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Array2D<T>& a);

    template<class T>
    class Array2D {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef std::vector<value_type>::iterator iterator;
        typedef std::vector<value_type>::const_iterator const_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        using VecType = std::vector<value_type>;
        using DualVecType = std::vector<VecType>;

        explicit Array2D(const DualVecType& input_data);

        template<typename IdxT>
        reference at(IdxT x, IdxT y)
        {
            auto x_long = static_cast<long long> (x);
            auto y_long = static_cast<long long> (y);
            return at_cardinal(x_cardinal(x_long), y_cardinal(y_long));
        }

        template<typename IdxT>
        NodeWrapper<value_type> node_at(IdxT x, IdxT y)
        {
            auto x_long = static_cast<long long> (x);
            auto y_long = static_cast<long long> (y);
            auto& val = at_cardinal(x_cardinal(x_long), y_cardinal(y_long));
            return NodeWrapper<T>{val, x_long, y_long};
        }

        reference at(Vec2D<long long> vec)
        {
            return at(vec.x, vec.y);
        }

        [[nodiscard]] size_type index_to_x_cardinal(size_t index) const
        {
            return index%size_y;
        }

        [[nodiscard]] long long index_to_actual_x(size_t index) const
        {
            return index_to_x_cardinal(index)+x_origin;
        }

        [[nodiscard]] size_type index_to_y_cardinal(size_t index) const
        {
            return index/size_y;
        }

        [[nodiscard]] long long index_to_actual_y(size_t index) const
        {
            return index_to_y_cardinal(index)+y_origin;
        }

        [[nodiscard]] size_type size() const
        {
            return this->data.size();
        }

        [[nodiscard]] size_type get_size_x() const
        {
            return size_x;
        }

        [[nodiscard]] size_type get_size_y() const
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
        iterator begin()
        {
            return data.begin();
        }

        iterator end()
        {
            return data.end();
        }

        const_iterator begin() const
        {
            return data.begin();
        }

        const_iterator end() const
        {
            return data.end();
        }

        const_iterator cbegin() const
        {
            return data.cbegin();
        }

        const_iterator cend() const
        {
            return data.cend();
        }

        // Row iterator
        RowIterator<T> row_iter();

    private:
        VecType data{};
        size_type size_x{};
        size_type size_y{};
        long long x_origin{0};
        long long y_origin{0};

        size_type x_cardinal(long long x);

        size_type y_cardinal(long long y);

        reference at_cardinal(const size_t& x_cardinal, const size_t& y_cardinal)
        {
            return data.at(cardinal_to_index(x_cardinal, y_cardinal));
        }

        size_type cardinal_to_index(const size_t& x_cardinal, const size_t& y_cardinal)
        {
            return (y_cardinal*size_x)+x_cardinal;
        }

    };

    template<class T>
    RowIterator<T> Array2D<T>::row_iter()
    {
        return RowIterator<T>{&data, get_size_x()};
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
    Array2D<T>::size_type Array2D<T>::y_cardinal(long long int y)
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
    Array2D<T>::size_type Array2D<T>::x_cardinal(long long int x)
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
    std::ostream& operator<<(std::ostream& os, const NodeWrapper<T>& nw)
    {
        os << "NodeWrapper{x=" << nw.x << " ,y=" << nw.y;
        os << " ,value=" << nw.value << "}";
        return os;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& os, const Array2D<T>& a)
    {

        size_t max_len{0};
        for (auto x : a) {
            std::stringstream ss;
            ss << x;
            size_t str_len{0};
            str_len = ss.str().length();
            if (str_len>max_len) {
                max_len = str_len;
            }
        }

        for (auto i{0}; i<a.data.size(); i++) {
            // Pre value insert
            if (i%a.size_x==0) {
                os << "|";
            }
            // Value insert
            std::stringstream ss;
            ss << a.data.at(i);
            os.fill(' ');
            os << std::setw(max_len) << ss.str();

            // Post value insert
            if ((i+1)%a.size_x==0) {
                os << "|\n";
            }
            else {
                os << ",";
            }
        }

        return os;
    }

}