#pragma once

#include <iostream>
#include <type_traits>
#include <concepts>
#include <cmath>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
class Point {
private:
    T _x{};
    T _y{};

public:
    Point() = default;
    Point(T x, T y) : _x(x), _y(y) {}

    Point(const Point&) = default;
    Point(Point&&) noexcept = default;

    Point& operator=(const Point&) = default;
    Point& operator=(Point&&) noexcept = default;

    T x() const noexcept { return _x; }
    T y() const noexcept { return _y; }

    bool operator==(const Point& other) const noexcept {
        return _x == other._x && _y == other._y;
    }

    bool operator!=(const Point& other) const noexcept {
        return !(*this == other);
    }

    Point operator-(const Point& other) const noexcept {
        return Point(_x - other._x, _y - other._y);
    }

    double dot(const Point& other) const noexcept {
        return static_cast<double>(_x) * static_cast<double>(other._x) +
               static_cast<double>(_y) * static_cast<double>(other._y);
    }

    double distanceTo(const Point& other) const noexcept {
        long double dx = static_cast<long double>(_x) - static_cast<long double>(other._x);
        long double dy = static_cast<long double>(_y) - static_cast<long double>(other._y);
        return std::sqrt(static_cast<double>(dx * dx + dy * dy));
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p._x << ", " << p._y << ")";
    }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        return is >> p._x >> p._y;
    }
};
