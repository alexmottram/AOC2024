#pragma once

#include "precompile_header.h"
#include "vector_3d.h"

namespace utils {

	template<typename coord_type, class value_type>
	class RefNode;

	// Forward assign Array operators
	template<typename coord_type, class value_type>
	std::ostream &operator<<(std::ostream &os, const RefNode<coord_type, value_type> &nw);

	template<typename coord_type, class value_type>
	class RefNode {
	public:
		value_type &value;
		coord_type x;
		coord_type y;

		RefNode(value_type &value, const coord_type &x, const coord_type &y)
				: value(value), x(x), y(y) {};

		friend std::ostream &operator
		<<<coord_type, value_type>(
		std::ostream &os,
		const RefNode<coord_type, value_type> &nw
		);

		Vec2D<coord_type> vector() const { return Vec2D<coord_type>{x, y}; };

		friend bool operator==(
				RefNode<coord_type, value_type> const &lhs,
				RefNode<coord_type, value_type> const &rhs
		) {
			return (&(lhs.value) == &(rhs.value));
		}

		friend bool operator<(
				RefNode<coord_type, value_type> const &lhs,
				RefNode<coord_type, value_type> const &rhs
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
	operator<<(std::ostream &os, const RefNode<coord_type, value_type> &rn) {
		os << "RefNodeType{x=" << rn.x << " ,y=" << rn.y;
		os << " ,value=" << rn.value << "}";
		return os;
	}

	template<typename coord_type, class value_type>
	class ConstNode;

	// Forward assign Array operators
	template<typename coord_type, class value_type>
	std::ostream &operator<<(std::ostream &os, const ConstNode<coord_type, value_type> &nw);

	template<typename coord_type, class value_type>
	class ConstNode {
	public:
		value_type value;
		coord_type x;
		coord_type y;

		ConstNode(const value_type &value, const coord_type &x, const coord_type &y)
				: value(value), x(x), y(y) {};

		ConstNode(const ConstNode &) = default;
		ConstNode(ConstNode &&) noexcept = default;
		ConstNode &operator=(const ConstNode &) = default;
		ConstNode &operator=(ConstNode &&) noexcept = default;
		~ConstNode() noexcept = default;

		friend std::ostream &operator
		<<<coord_type, value_type>(
				std::ostream &os,
				const ConstNode<coord_type, value_type> &nw
		);

		Vec2D<coord_type> vector() const { return Vec2D<coord_type>{x, y}; };

		friend bool operator==(
				ConstNode<coord_type, value_type> const &lhs,
				ConstNode<coord_type, value_type> const &rhs
		) {
			return (&(lhs.value) == &(rhs.value));
		}

		friend bool operator<(
				ConstNode<coord_type, value_type> const &lhs,
				ConstNode<coord_type, value_type> const &rhs
		) {
			return (
					(lhs.y < rhs.y) ||
					((lhs.y == rhs.y) && (lhs.x < rhs.x)) ||
					((lhs.y == rhs.y) && (lhs.x == rhs.x) && (lhs.value < rhs.value))
			);
		}
	};

	template<typename coord_type, class value_type>
	std::ostream &operator<<(std::ostream &os, const ConstNode<coord_type, value_type> &rn) {
		os << "ConstNode{x=" << rn.x << " ,y=" << rn.y;
		os << " ,value=" << rn.value << "}";
		return os;
	}

}