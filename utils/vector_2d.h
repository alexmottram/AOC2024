#pragma once

#include "precompile_header.h"
#include "string_tools.h"

namespace utils {

    template<typename T>
    struct Vec2D {
        T x;
        T y;

        Vec2D(T x=0, T y=0) : x(x), y(y) { }

        ~Vec2D() = default;
        Vec2D(const Vec2D<T>& t) = default;
        Vec2D& operator=(const Vec2D<T>& t) = default;

        Vec2D(int x=0, int y=0) requires(std::is_same_v<long long, T>) :
        x(1),  y(1) {
            std::cout << "Called int to long long creator" << std::endl;
        }

        Vec2D(const std::string& str_input, const std::string& delimiter)        {
            auto string_vec = utils::string_to_vector_type<T>(str_input,
                    delimiter,
                    true);
            if (string_vec.size()!=2) {
                throw std::runtime_error("Vector string must have 2 elements only.");
            }
            x = string_vec.at(0);
            y = string_vec.at(1);
        }

        friend bool operator<(const Vec2D& lhs, const Vec2D& rhs)
        {
            return ((lhs.x<rhs.x) || (lhs.x==rhs.x && lhs.y<rhs.y));
        }

        friend bool operator>(const Vec2D& lhs, const Vec2D& rhs)
        {
            return rhs<lhs;
        }

        friend bool operator==(const Vec2D& lhs, const Vec2D& rhs)
        {
            return ((lhs.x==rhs.x) && (lhs.y==rhs.y));
        }

        friend Vec2D operator+(const Vec2D& lhs, const Vec2D& rhs)
        {
            return Vec2D{lhs.x+rhs.x, lhs.y+rhs.y};
        }

        friend Vec2D operator-(const Vec2D& lhs, const Vec2D& rhs)
        {
            return Vec2D{lhs.x-rhs.x, lhs.y-rhs.y};
        }

        Vec2D& operator+=(const Vec2D& other)
        {
            *this = *this+other;
            return *this;
        }

        Vec2D& operator-=(const Vec2D& other)
        {
            *this = *this-other;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& os, const Vec2D& l)
        {
            os << "Vec2D{x=" << l.x << ",y=" << l.y << "}";
            return os;
        }
    };

}