#pragma once

#include "Figure.h"

#include <array>
#include <memory>
#include <cmath>

template <Scalar T>
class Pentagon : public Figure<T> {
public:
    static constexpr size_t n = 5;

    Pentagon() {
        for (auto& v : vertices)
            v = std::make_unique<Point<T>>();
    }

    explicit Pentagon(const std::array<Point<T>, n>& points) {
        for (size_t i = 0; i < n; ++i)
            vertices[i] = std::make_unique<Point<T>>(points[i]);
    }

    Pentagon(const Pentagon& other) {
        for (size_t i = 0; i < n; ++i)
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
    }

    Pentagon& operator=(const Pentagon& other) {
        if (this == &other)
            return *this;

        for (size_t i = 0; i < n; ++i)
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);

        return *this;
    }

    Pentagon(Pentagon&& other) noexcept {
        for (size_t i = 0; i < n; ++i)
            vertices[i] = std::move(other.vertices[i]);
    }

    Pentagon& operator=(Pentagon&& other) noexcept {
        if (this == &other)
            return *this;

        for (size_t i = 0; i < n; ++i)
            vertices[i] = std::move(other.vertices[i]);

        return *this;
    }

    Point<T> center() const override {
        T sumX{0}, sumY{0};

        for (const auto& v : vertices) {
            sumX += v->x();
            sumY += v->y();
        }

        return Point<T>(sumX / n, sumY / n);
    }

    operator double() const override {
        long double area = 0.0L;

        for (size_t i = 0; i < n; ++i) {
            size_t j = (i + 1) % n;
            area += static_cast<long double>(vertices[i]->x()) * vertices[j]->y()
                  - static_cast<long double>(vertices[j]->x()) * vertices[i]->y();
        }

        return std::abs(static_cast<double>(area / 2.0L));
    }

    bool equals(const Figure<T>& other) const override {
        const auto* p = dynamic_cast<const Pentagon<T>*>(&other);
        if (!p)
            return false;

        for (size_t i = 0; i < n; ++i)
            if (*(vertices[i]) != *(p->vertices[i]))
                return false;

        return true;
    }

protected:
    void print(std::ostream& os) const override {
        os << "Pentagon: ";
        for (const auto& v : vertices)
            os << *v << " ";
    }

    void read(std::istream& is) override {
        for (auto& v : vertices)
            is >> *v;
    }

private:
    std::array<std::unique_ptr<Point<T>>, n> vertices;
};
