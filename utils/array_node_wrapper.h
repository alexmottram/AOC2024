#pragma once

#include "precompile_header.h"
#include "vector_3d.h"

namespace utils {
	template<typename coord_type, class value_type>
	class NodeWrapper;

	// Forward assign Array operators
	template<typename coord_type, class value_type>
	std::ostream &operator<<(std::ostream &os, const NodeWrapper<coord_type, value_type> &nw);

	template<typename coord_type, class value_type>
	class NodeWrapper {
	public:

		NodeWrapper(value_type &value, coord_type x, coord_type y)
				: _value(value), _x(x), _y(y) {};

		friend std::ostream &operator<< <coord_type, value_type>(
				std::ostream &os,
				const NodeWrapper<coord_type, value_type> &nw
		);

		[[nodiscard]] size_t x() const {return _x;}
		[[nodiscard]] size_t y() const {return _y;}
		const value_type & value() const {return _value;}
		value_type& value() {
			return const_cast<value_type&>(const_cast<const NodeWrapper*>(this)->value());
		}

		Vec2D<coord_type> vector() const { return Vec2D<coord_type>{x(), y()}; };

		friend bool operator==(
				NodeWrapper<coord_type, value_type> const &lhs,
				NodeWrapper<coord_type, value_type> const &rhs
		) {
			return (&(lhs.value()) == &(rhs.value()));
		}

		friend bool operator<(
				NodeWrapper<coord_type, value_type> const &lhs,
				NodeWrapper<coord_type, value_type> const &rhs
		) {
			return (
					(lhs.y() < rhs.y()) ||
					((lhs.y() == rhs.y()) && (lhs.x() < rhs.x())) ||
					((lhs.y() == rhs.y()) && (lhs.x() == rhs.x()) && (lhs.value() < rhs.value()))
			);
		}

	private:
		value_type &_value;
		const coord_type _x;
		const coord_type _y;

	};

	template<typename coord_type, class value_type>
	std::ostream &
	operator<<(std::ostream &os, const NodeWrapper<coord_type, value_type> &nw) {
		os << "NodeWrapper{x=" << nw.x() << " ,y=" << nw.y();
		os << " ,value=" << nw.value() << "}";
		return os;
	}

}