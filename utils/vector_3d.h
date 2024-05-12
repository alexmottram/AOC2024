#pragma once

#include "precompile_header.h"
#include "string_tools.h"

namespace utils {

    template<typename T>
    struct Vec3D {
        T x{0};
        T y{0};
        T z{0};

        Vec3D(T x, T y, T z)
                :x(x), y(y), z(z) { }

        Vec3D(const std::string& str_input, const std::string& delimiter)
        {
            auto string_vec = utils::string_to_vector_type<T>(str_input,
                    delimiter,
                    true);
            if (string_vec.size()!=3) {
                throw std::runtime_error("Vector string must have 3 elements only.");
            }
            x = string_vec.at(0);
            y = string_vec.at(1);
            z = string_vec.at(2);
        }

        friend bool operator<(const Vec3D& lhs, const Vec3D& rhs)
        {
            return (
                    (lhs.x<rhs.x) ||
                            (lhs.x==rhs.x && lhs.y<rhs.y) ||
                            (lhs.x==rhs.x && lhs.y==rhs.y && lhs.z<rhs.z)
            );
        }

        friend bool operator>(const Vec3D& lhs, const Vec3D& rhs)
        {
            return rhs<lhs;
        }

        friend bool operator==(const Vec3D& lhs, const Vec3D& rhs)
        {
            return ((lhs.x==rhs.x) && (lhs.y==rhs.y) && (lhs.z==rhs.z));
        }

        friend Vec3D operator+(const Vec3D& lhs, const Vec3D& rhs)
        {
            return Vec3D{lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z};
        }

        friend Vec3D operator-(const Vec3D& lhs, const Vec3D& rhs)
        {
            return Vec3D{lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z};
        }

        Vec3D& operator+=(Vec3D const& other)
        {
            *this = *this+other;
            return *this;
        }

        Vec3D& operator-=(Vec3D const& other)
        {
            *this = *this-other;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& os, const Vec3D& l)
        {
            os << "Vec3D{x=" << l.x << ",y=" << l.y << ",z=" << l.z << "}";
            return os;
        }
    };
}