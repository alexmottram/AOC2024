//
// Created by Alexander Mottram on 01/12/2023.
//
#pragma once

#include "precompile_header.h"

namespace utils
{

	struct Vec2D
	{
		long long x;
		long long y;

		friend bool operator<(Vec2D const& lhs, Vec2D const& rhs);
		friend bool operator>(Vec2D const& lhs, Vec2D const& rhs);

		friend bool operator==(Vec2D const& lhs, Vec2D const& rhs);

		friend Vec2D operator+(Vec2D const& lhs, Vec2D const& rhs);

		friend Vec2D operator-(Vec2D const& lhs, Vec2D const& rhs);

		friend std::ostream& operator<<(std::ostream& os, const Vec2D& l);
	};
}