#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>
#include <concepts>
#include <type_traits>

template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

template<Scalar T>
struct Point {
    T x{};
    T y{};

    Point() = default;
    Point(T X, T Y) : x(X), y(Y) {}

    double distanceTo(const Point& other) const {
        long double dx = static_cast<long double>(x) - static_cast<long double>(other.x);
        long double dy = static_cast<long double>(y) - static_cast<long double>(other.y);
        return std::sqrt((double)(dx * dx + dy * dy));
    }
};

template<Scalar T>
inline std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

template<Scalar T>
inline std::istream& operator>>(std::istream& is, Point<T>& p) {
    return is >> p.x >> p.y;
}

#endif // POINT_H
