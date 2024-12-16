//
// Created by Alexander Mottram on 29/04/2024.
//
#pragma once

#include "precompile_header.h"
#include "vector_3d.h"

namespace utils {

	template<typename value_type, typename size_type>
	struct NodeIterator;
	template<typename value_type, typename size_type>
	struct NodeRow;
	template<typename value_type, typename size_type>
	struct NodeRowIterator;

	// Forward assign operators (mainly ostream)
	template<typename value_type, typename size_type>
	std::ostream &operator<<(std::ostream &os, const NodeIterator<value_type, size_type> &r);

	template<typename value_type, typename size_type>
	struct NodeIterator {
		typedef std::vector<value_type> VecType;
		typedef RefNode<size_type, value_type> NodeType;

		// Iterator constructors here...
		NodeIterator(value_type *ptr, VecType *data_ptr, size_type idx, size_type row_size)
				: m_ptr(ptr), data_ptr(data_ptr), index(idx), row_size(row_size) {}

		NodeIterator(VecType *data_ptr, size_type row_size)
				: m_ptr(&(*data_ptr->begin())), data_ptr(data_ptr), index(0), row_size(row_size) {}

		NodeType operator*() const { return NodeType{*m_ptr, x(), y()}; }

		NodeType operator->() { return NodeType{*m_ptr, x(), y()}; }

		// Prefix increment
		NodeIterator<value_type, size_type> &operator++() {
			m_ptr++;
			index++;
			return *this;
		}

		// Postfix increment
		NodeIterator<value_type, size_type> operator++(int) {
			NodeIterator<value_type, size_type> tmp{m_ptr, data_ptr, index, row_size};
			++(*this);
			return tmp;
		}

		friend bool operator==(const NodeIterator &a, const NodeIterator &b) {
			return a.m_ptr == b.m_ptr;
		};

		friend bool operator!=(const NodeIterator &a, const NodeIterator &b) {
			return a.m_ptr != b.m_ptr;
		};

		friend std::ostream &operator<<<value_type, size_type>(
				std::ostream &os,
				const NodeIterator<value_type, size_type> &r
		);

		[[nodiscard]] size_type x() const {
			return index % row_size;
		}

		[[nodiscard]] size_type y() const {
			return index / row_size;
		}

		auto begin() {
			return NodeIterator<value_type, size_type>(
					&(*data_ptr->begin()), data_ptr, 0, row_size
			);
		}

		auto end() {
			return NodeIterator<value_type, size_type>(
					&(*data_ptr->end()), data_ptr, data_ptr->size(), row_size
			);
		}

		auto begin() const {
			return NodeIterator<value_type, size_type>(
					&(*data_ptr->begin()), data_ptr, 0, row_size
			);
		}

		auto end() const {
			return NodeIterator<value_type, size_type>(
					&(*data_ptr->end()), data_ptr, data_ptr->size(), row_size
			);
		}

	private:
		value_type *m_ptr;
		VecType *data_ptr;
		size_type index;
		const size_type row_size;
	};

	template<class value_type, typename size_type>
	struct NodeRow {
		using NodeType = RefNode<size_type, value_type>;

		// Iterator constructors here...
		NodeRow(value_type *ptr, size_type y, size_type row_size)
				: m_ptr(ptr), row_start(ptr), x(0), y(y), row_size(row_size) {}

		NodeRow(value_type *ptr, value_type *row_start, size_type x, size_type y, size_type row_size)
				: m_ptr(ptr), row_start(row_start), x(x), y(y), row_size(row_size) {}

		NodeType operator*() const { return NodeType{*m_ptr, x, y}; }

		NodeType operator->() { return NodeType{*m_ptr, x, y}; }

		// Prefix increment
		NodeRow<value_type, size_type> &operator++() {
			m_ptr++;
			x++;
			return *this;
		}

		// Postfix increment
		NodeRow<value_type, size_type> operator++(int) {
			NodeRow<value_type, size_type> tmp{m_ptr, row_start, x, row_size};
			++(*this);
			return tmp;
		}

		friend bool operator==(const NodeRow &a, const NodeRow &b) {
			return a.m_ptr == b.m_ptr;
		};

		friend bool operator!=(const NodeRow &a, const NodeRow &b) {
			return a.m_ptr != b.m_ptr;
		};

		auto row_end() { return row_start + row_size; }

		auto begin() { return NodeRow<value_type, size_type>(row_start, y, row_size); }

		auto end() { return NodeRow<value_type, size_type>(row_end(), row_start, row_size, y, row_size); }

		auto begin() const { return NodeRow<value_type, size_type>(row_start, y, row_size); }

		auto end() const { return NodeRow<value_type, size_type>(row_end(), row_start, row_size, y, row_size); }

	private:
		value_type *m_ptr;
		value_type *row_start;
		size_type x;
		const size_type y;
		const size_t row_size;
	};

	template<typename value_type, typename size_type>
	struct NodeRowIterator {

		// Iterator constructors here...
		NodeRowIterator(std::vector<value_type> *vector_ptr, size_type row_size)
				: m_ptr(&(*vector_ptr->begin())), m_vector_ptr(vector_ptr), y(0), row_size(row_size) {}

		NodeRowIterator(value_type *ptr, std::vector<value_type> *vector_ptr, size_type y, size_type row_size)
				: m_ptr(ptr), m_vector_ptr(vector_ptr), y(y), row_size(row_size) {}


		NodeRow<value_type, size_type> operator*() const { return NodeRow<value_type, size_type>{m_ptr, y, row_size}; }

		NodeRow<value_type, size_type> operator->() { return NodeRow<value_type, size_type>{m_ptr, y, row_size}; }

		// Prefix increment
		NodeRow<value_type, size_type> operator++() {
			m_ptr += row_size;
			y++;
			return NodeRow<value_type, size_type>{m_ptr, y, row_size};
		}

		// Postfix increment
		NodeRow<value_type, size_type> operator++(int) {
			NodeRow<value_type, size_type> tmp = NodeRow<value_type, size_type>{m_ptr, y, row_size};
			(*this) += row_size;
			return tmp;
		}

		friend bool operator==(const NodeRowIterator &a, const NodeRowIterator &b) {
			return a.m_ptr == b.m_ptr;
		};

		friend bool operator!=(const NodeRowIterator &a, const NodeRowIterator &b) {
			return a.m_ptr != b.m_ptr;
		};

		size_type max_y() const {
			return (m_vector_ptr->size() / row_size) - 1;
		}

		auto row_iterator_begin() {
			return &(*m_vector_ptr->begin());
		}

		auto row_iterator_end() {
			return &(*m_vector_ptr->end());
		}

		auto begin() {
			return NodeRowIterator<value_type, size_type>(row_iterator_begin(), m_vector_ptr, 0, row_size);
		}

		auto end() {
			return NodeRowIterator<value_type, size_type>(row_iterator_end(), m_vector_ptr, max_y(), row_size);
		}

		auto begin() const {
			return NodeRowIterator<value_type, size_type>(row_iterator_begin(), m_vector_ptr, 0, row_size);
		}

		auto end() const {
			return NodeRowIterator<value_type, size_type>(row_iterator_end(), m_vector_ptr, max_y(), row_size);
		}

	private:
		value_type *m_ptr;
		std::vector<value_type> *m_vector_ptr;
		size_t y;
		const size_t row_size;
	};

	// Implement << operator methods
	template<typename value_type, typename size_type>
	std::ostream &operator<<(std::ostream &os, const NodeIterator<value_type, size_type> &node) {
		os << "NodeIterator{curr_mem=" << node.m_ptr;
		os << ", x=" << node.x() << ", y=" << node.y();
		os << ", curr_val=" << *node << ", len=" << node.row_size << "}";
		return os;
	}

}