#pragma once

#include "precompile_header.h"
#include "vector_tools.h"

namespace utils {
    template<typename T>
    class NodeWrapper;

    // Forward assign Array operators
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const NodeWrapper<T>& nw);

    template<class T>
    class NodeWrapper {
    public:
        T& value;
        const long long x;
        const long long y;

        NodeWrapper(T& value, long long x, long long y)
                :value(value), x(x), y(y) { };

        friend std::ostream& operator
        <<<T>(
        std::ostream& os,
        const NodeWrapper<T>& nw
        );

        Vec2D vector() { return Vec2D{x, y}; };

    };
}