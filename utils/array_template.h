//
// Created by Alexander Mottram on 04/12/2023.
//
#pragma once

#include "precompile_header.h"
#include "vector_3d.h"
#include "array_node_wrapper.h"
#include "array_iterators.h"
#include "array_node_iterators.h"

namespace utils
{
    template <typename T>
    class Array2D;

    // Forward assign Array operators
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Array2D<T>& a);

    template <class T>
    class Array2D
    {
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
        using NodeType = NodeWrapper<size_type, value_type>;
        using ConstNodeType = ConstNodeWrapper<size_type, value_type>;

        explicit Array2D(const DualVecType& input_data);

        explicit Array2D(const std::vector<std::string>& input_strings);

        template <typename x_size_type, typename y_size_type>
        reference at(x_size_type x, y_size_type y)
        {
            if (!coords_in_array(x, y))
            {
                throw std::out_of_range("Array2D::at");
            }
            const auto x_coord = static_cast<size_type>(x);
            const auto y_coord = static_cast<size_type>(y);
            return at_index(coords_to_idx(x_coord, y_coord));
        }

        template <typename x_size_type, typename y_size_type>
        value_type at(x_size_type x, y_size_type y) const
        {
            if (!coords_in_array(x, y))
            {
                throw std::out_of_range("Array2D::at");
            }
            const auto x_coord = static_cast<size_t>(x);
            const auto y_coord = static_cast<size_t>(y);
            return at_index(coords_to_idx(x_coord, y_coord));
        }

        template <typename vec_size_type>
        reference at(Vec2D<vec_size_type> vec)
        {
            if (!vector_in_array(vec))
            {
                throw std::out_of_range("Array2D::at");
            }
            return at(vec.x, vec.y);
        }

        template <typename vec_size_type>
        value_type at(Vec2D<vec_size_type> vec) const
        {
            return at(vec.x, vec.y);
        }

        template <typename x_size_type, typename y_size_type>
        NodeType node_at(const x_size_type& x, const y_size_type& y)
        {
            reference val = at(x, y);
            return NodeType{val, static_cast<size_t>(x), static_cast<size_t>(y)};
        }

        template <typename x_size_type, typename y_size_type>
        ConstNodeType const_node_at(const x_size_type& x, const y_size_type& y) const
        {
            const_reference val = at(x, y);
            return ConstNodeType{val, static_cast<size_t>(x), static_cast<size_t>(y)};
        }

        reference at_index(size_t idx)
        {
            return data.at(idx);
        }

        value_type at_index(size_t idx) const
        {
            return data.at(idx);
        }

        template <typename vec_size_type>
        bool vector_in_array(const Vec2D<vec_size_type> vec) const
        {
            return coords_in_array(vec.x, vec.y);
        }

        template <typename x_size_type, typename y_size_type>
        bool coords_in_array(x_size_type x_val, y_size_type y_val) const
        {
            return x_in_array(x_val) and y_in_array(y_val);
        }


        template <typename x_size_type>
        bool x_in_array(const x_size_type x_val) const
        {
            if (x_val < 0) { return false; }
            const auto x_val_cast = static_cast<size_type>(x_val);
            return x_val_cast < size_x;
        }

        template <typename y_size_type>
        bool y_in_array(const y_size_type y_val) const
        {
            if (y_val < 0) { return false; }
            const auto y_val_cast = static_cast<size_type>(y_val);
            return y_val_cast < size_y;
        }

        std::set<NodeType> find(const_reference val)
        {
            std::set<NodeType> found_nodes;
            for (auto x_coord{0}; x_coord < size_x; x_coord++)
            {
                for (auto y_coord{0}; y_coord < size_y; y_coord++)
                {
                    auto& val_at_coords = at(x_coord, y_coord);
                    if (val_at_coords == val)
                    {
                        found_nodes.emplace(val_at_coords, x_coord, y_coord);
                    }
                }
            }
            return found_nodes;
        }

        std::set<NodeType> adjacent(const size_type x, const size_type y, const bool include_diagonals = false)
        {
            std::set<NodeType> adjacent_nodes{};
            bool x_in_array = (x >= 0 && x < size_x);
            bool y_in_array = (y >= 0 && y < size_y);

            // Left node
            if (x > 0 && y_in_array)
            {
                adjacent_nodes.emplace(node_at(x - 1, y));
            }
            // Right node
            if ((x < (size_x - 1)) && y_in_array)
            {
                adjacent_nodes.emplace(node_at(x + 1, y));
            }
            // Up node
            if (y > 0 && x_in_array)
            {
                adjacent_nodes.emplace(node_at(x, y - 1));
            }
            // Down node
            if ((y < (size_y - 1)) && x_in_array)
            {
                adjacent_nodes.emplace(node_at(x, y + 1));
            }

            if (include_diagonals)
            {
                bool up_in_array = y + 1 < size_y;
                bool down_in_array = y > 0;
                bool left_in_array = x > 0;
                bool right_in_array = x + 1 < size_x;

                // Up-Left node
                if (up_in_array && left_in_array)
                {
                    adjacent_nodes.emplace(node_at(x - 1, y + 1));
                }

                // Up-Right node
                if (up_in_array && right_in_array)
                {
                    adjacent_nodes.emplace(node_at(x + 1, y + 1));
                }

                // Down-Left node
                if (down_in_array && left_in_array)
                {
                    adjacent_nodes.emplace(node_at(x - 1, y - 1));
                }

                // Down-Right node
                if (down_in_array && right_in_array)
                {
                    adjacent_nodes.emplace(node_at(x + 1, y - 1));
                }
            }

            return adjacent_nodes;
        }

        std::set<NodeType> adjacent(NodeType node, bool include_diagonals = false)
        {
            return adjacent(node.x, node.y, include_diagonals);
        }

        [[nodiscard]] size_type coords_to_idx(const size_type x, const size_type y) const
        {
            return (y * size_x) + x;
        }

        [[nodiscard]] size_type index_to_x(const size_t index) const
        {
            return index % size_y;
        }

        [[nodiscard]] size_type index_to_y(const size_t index) const
        {
            return index / size_y;
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
                (lhs.size() < rhs.size())
                || ((lhs.size() == rhs.size()) && (lhs.data < rhs.data))
            );
        }

        friend bool operator==(Array2D<T> const& lhs, Array2D<T> const& rhs)
        {
            return (lhs.get_size_x() == rhs.get_size_x())
                && (lhs.get_size_y() == rhs.get_size_y())
                && (lhs.data == rhs.data);
        }

        friend std::ostream& operator
        <<<T>(
            std::ostream& os,
            const Array2D<T>& a
        );

        // Standard vector based begin and ends
        iterator begin() { return data.begin(); }

        iterator end() { return data.end(); }

        const_iterator begin() const { return data.begin(); }

        const_iterator end() const { return data.end(); }

        const_iterator cbegin() const { return data.cbegin(); }

        const_iterator cend() const { return data.cend(); }

        // Row iterator
        RowIterator<value_type> row_iter()
        {
            return RowIterator<T>{&data, get_size_x()};
        }

        NodeIterator<value_type, size_type> node_iter()
        {
            return NodeIterator<value_type, size_type>{&data, get_size_x()};
        }

        ConstNodeIterator<value_type, size_type> const_node_iter() const
        {
            return ConstNodeIterator<value_type, size_type>{&data, get_size_x()};
        }

        NodeRowIterator<value_type, size_type> node_row_iter()
        {
            return NodeRowIterator<value_type, size_type>{&data, get_size_x()};
        }

    private:
        VecType data{};
        size_type size_x{};
        size_type size_y{};
    };

    template <class T>
    Array2D<T>::Array2D(const DualVecType& input_data)
    {
        this->size_y = input_data.size();
        this->size_x = input_data.front().size();
        for (const auto& row : input_data)
        {
            if (row.size() != this->size_x)
            {
                throw std::invalid_argument("Uneven subvector sizes.");
            }
            for (auto val : row)
            {
                this->data.push_back(val);
            }
        }
    }

    template <class T>
    Array2D<T>::Array2D(const std::vector<std::string>& input_data)
    {
        this->size_y = input_data.size();
        this->size_x = input_data.front().size();
        for (const auto& row : input_data)
        {
            auto vals = utils::string_to_vector_type<T>(row);
            if (vals.size() != this->size_x)
            {
                throw std::invalid_argument("Uneven subvector sizes.");
            }
            for (auto val : vals)
            {
                this->data.push_back(val);
            }
        }
    }

    template <class T>
    std::ostream& operator<<(std::ostream& os, const Array2D<T>& a)
    {
        size_t max_len{0};
        for (auto x : a)
        {
            std::stringstream ss;
            ss << x;
            size_t str_len{0};
            str_len = ss.str().length();
            if (str_len > max_len)
            {
                max_len = str_len;
            }
        }

        for (auto i{0}; i < a.data.size(); i++)
        {
            // Pre value insert
            if (i % a.size_x == 0)
            {
                os << "|";
            }
            // Value insert
            std::stringstream ss;
            ss << a.data.at(i);
            os.fill(' ');
            os << std::setw(max_len) << ss.str();

            // Post value insert
            if ((i + 1) % a.size_x == 0)
            {
                os << "|\n";
            }
            else
            {
                os << ",";
            }
        }

        return os;
    }
}
