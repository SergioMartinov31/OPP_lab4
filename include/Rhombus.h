#pragma once

#include "Figure.h"

#include <array>
#include <memory>
#include <cmath>

template <Scalar T>
class Rhombus : public Figure<T> {
public:
    static constexpr size_t n = 4;

    Rhombus() {
        for (auto& v : vertices)
            v = std::make_unique<Point<T>>();
    }

    Rhombus(const Point<T>& a, const Point<T>& b,
            const Point<T>& c, const Point<T>& d) {
        vertices[0] = std::make_unique<Point<T>>(a);
        vertices[1] = std::make_unique<Point<T>>(b);
        vertices[2] = std::make_unique<Point<T>>(c);
        vertices[3] = std::make_unique<Point<T>>(d);
    }

    Rhombus(const Rhombus& other) {
        for (size_t i = 0; i < n; ++i)
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
    }

    Rhombus& operator=(const Rhombus& other) {
        if (this == &other)
            return *this;

        for (size_t i = 0; i < n; ++i)
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);

        return *this;
    }

    Rhombus(Rhombus&& other) noexcept {
        for (size_t i = 0; i < n; ++i)
            vertices[i] = std::move(other.vertices[i]);
    }

    Rhombus& operator=(Rhombus&& other) noexcept {
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
        const auto* r = dynamic_cast<const Rhombus<T>*>(&other);
        if (!r)
            return false;

        for (size_t i = 0; i < n; ++i)
            if (*(vertices[i]) != *(r->vertices[i]))
                return false;

        return true;
    }

protected:
    void print(std::ostream& os) const override {
        os << "Rhombus: ";
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
