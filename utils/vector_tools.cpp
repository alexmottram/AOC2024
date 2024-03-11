//
// Created by Alexander Mottram on 03/12/2023.
//

#include "vector_tools.h"

namespace utils {

std::ostream &operator<<(std::ostream &os, const Vec2D &l) {
	os << "Vec2D{x=" << l.x << ",y=" << l.y << "}";
	return os;
}

bool operator<(const Vec2D &lhs, const Vec2D &rhs) {
	return ((lhs.x < rhs.x) || (lhs.x == rhs.x && lhs.y < rhs.y));
}

bool operator==(const Vec2D &lhs, const Vec2D &rhs) {
	return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

Vec2D operator+(const Vec2D &lhs, const Vec2D &rhs) {
	return Vec2D{lhs.x + rhs.x, lhs.y + rhs.y};
}

Vec2D operator-(const Vec2D &lhs, const Vec2D &rhs) {
	return Vec2D{lhs.x - rhs.x, lhs.y - rhs.y};
}
}