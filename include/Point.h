#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>
#include <concepts>
#include <type_traits>

template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

template<Scalar T>
class Point {
public:
    T x{0};
    T y{0};

    Point() = default;
    Point(T X, T Y) : x(X), y(Y) {}

    bool operator==(const Point& other) const noexcept {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const noexcept {
        return !(*this == other);
    }

    Point operator-(const Point& other) const noexcept {
        return Point(x - other.x, y - other.y);
    }

    double dot(const Point& other) const noexcept {
        return static_cast<double>(x) * static_cast<double>(other.x) +
               static_cast<double>(y) * static_cast<double>(other.y);
    }

    double distanceTo(const Point& other) const noexcept {
        long double dx = static_cast<long double>(x) - static_cast<long double>(other.x);
        long double dy = static_cast<long double>(y) - static_cast<long double>(other.y);
        return std::sqrt(static_cast<double>(dx * dx + dy * dy));
    }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        return is >> p.x >> p.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }

    ~Point() = default;
};

#endif 
