#pragma once

#include "precompile_header.h"
#include "vector_3d.h"

namespace utils {
	template<typename coord_type, class value_type>
	class NodeWrapper;

	// Forward assign Array operators
	template<typename coord_type, class value_type>
	std::ostream &
	operator<<(std::ostream &os, const NodeWrapper<coord_type, value_type> &nw);

	template<typename coord_type, class value_type>
	class NodeWrapper {
	public:
		value_type &value;
		const coord_type x;
		const coord_type y;

		NodeWrapper(value_type &value, coord_type x, coord_type y)
				: value(value), x(x), y(y) {};

		friend std::ostream &operator
		<<<coord_type, value_type>(
		std::ostream &os,
		const NodeWrapper<coord_type, value_type> &nw
		);

		Vec2D<coord_type> vector() const { return Vec2D<coord_type>{x, y}; };

		friend bool operator==(
				NodeWrapper<coord_type, value_type> const &lhs,
				NodeWrapper<coord_type, value_type> const &rhs
		) {
			return (&(lhs.value) == &(rhs.value));
		}

		friend bool operator<(
				NodeWrapper<coord_type, value_type> const &lhs,
				NodeWrapper<coord_type, value_type> const &rhs
		) {
			return (
					(lhs.y < rhs.y) ||
					((lhs.y == rhs.y) && (lhs.x < rhs.x)) ||
					((lhs.y == rhs.y) && (lhs.x == rhs.x) && (lhs.value < rhs.value))
			);
		}


	};

	template<typename coord_type, class value_type>
	class ConstNodeWrapper;

	// Forward assign Array operators
	template<typename coord_type, class value_type>
	std::ostream &
	operator<<(std::ostream &os, const ConstNodeWrapper<coord_type, value_type> &nw);

	template<typename coord_type, class value_type>
	class ConstNodeWrapper {
	public:
		const value_type &value;
		const coord_type x;
		const coord_type y;

		ConstNodeWrapper(const value_type &value, coord_type x, coord_type y)
				: value(value), x(x), y(y) {};

		friend std::ostream &operator
		<<<coord_type, value_type>(
		std::ostream &os,
		const ConstNodeWrapper<coord_type, value_type> &nw
		);

		Vec2D<coord_type> vector() const { return Vec2D<coord_type>{x, y}; };

		friend bool operator==(
				ConstNodeWrapper<coord_type, value_type> const &lhs,
				ConstNodeWrapper<coord_type, value_type> const &rhs
		) {
			return (&(lhs.value) == &(rhs.value));
		}

		friend bool operator<(
				ConstNodeWrapper<coord_type, value_type> const &lhs,
				ConstNodeWrapper<coord_type, value_type> const &rhs
		) {
			return (
					(lhs.y < rhs.y) ||
					((lhs.y == rhs.y) && (lhs.x < rhs.x)) ||
					((lhs.y == rhs.y) && (lhs.x == rhs.x) && (lhs.value < rhs.value))
			);
		}

	};

	template<typename coord_type, class value_type>
	std::ostream &
	operator<<(std::ostream &os, const NodeWrapper<coord_type, value_type> &nw) {
		os << "NodeWrapper{x=" << nw.x << " ,y=" << nw.y;
		os << " ,value=" << nw.value << "}";
		return os;
	}

	template<typename coord_type, class value_type>
	std::ostream &
	operator<<(std::ostream &os, const ConstNodeWrapper<coord_type, value_type> &nw) {
		os << "ConstNodeWrapper{x=" << nw.x << " ,y=" << nw.y;
		os << " ,value=" << nw.value << "}";
		return os;
	}

}