#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Figure.h"
#include "Point.h"
#include <array>
#include <memory>
#include <cmath>
#include <stdexcept>

template<Scalar T>
class Trapezoid : public Figure<T> {
private:
    static constexpr int n = 4;
    std::array<std::unique_ptr<Point<T>>, n> vertices;

public:
    Trapezoid() {
        for (auto& v : vertices)
            v = std::make_unique<Point<T>>();
    }

    Trapezoid(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d) {
        vertices[0] = std::make_unique<Point<T>>(a);
        vertices[1] = std::make_unique<Point<T>>(b);
        vertices[2] = std::make_unique<Point<T>>(c);
        vertices[3] = std::make_unique<Point<T>>(d);
    }

    Trapezoid(const Trapezoid& other) {
        for (int i = 0; i < n; ++i)
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
    }

    Trapezoid(Trapezoid&& other) noexcept {
        for (int i = 0; i < n; ++i)
            vertices[i] = std::move(other.vertices[i]);
    }

    Trapezoid& operator=(const Trapezoid& other) {
        if (this == &other) return *this;
        for (int i = 0; i < n; ++i)
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        return *this;
    }

    Trapezoid& operator=(Trapezoid&& other) noexcept {
        if (this == &other) return *this;
        for (int i = 0; i < n; ++i)
            vertices[i] = std::move(other.vertices[i]);
        return *this;
    }

    void print(std::ostream& os) const override {
        os << "Trapezoid: ";
        for (const auto& v : vertices)
            os << *v << " ";
    }

    void read(std::istream& is) override {
        for (auto& v : vertices)
            is >> *v;
        if (!validate())
            throw std::invalid_argument("Invalid trapezoid: points do not form a valid shape.");
    }

    bool validate() const override {
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (*vertices[i] == *vertices[j])
                    return false;
        return surface() > 1e-9;
    }

    Point<T> center() const override {
        T cx = 0, cy = 0;
        for (const auto& v : vertices) {
            cx += v->x;
            cy += v->y;
        }
        return Point<T>{cx / n, cy / n};
    }

    double surface() const override {
        long double s = 0;
        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            s += (long double)vertices[i]->x * vertices[j]->y -
                 (long double)vertices[j]->x * vertices[i]->y;
        }
        return std::abs((double)(s / 2.0L));
    }

    operator double() const override {
        return surface();
    }

    bool operator==(const Figure<T>& other) const override {
        const Trapezoid<T>* o = dynamic_cast<const Trapezoid<T>*>(&other);
        if (!o) return false;
        for (int i = 0; i < n; ++i)
            if (*vertices[i] != *o->vertices[i])
                return false;
        return true;
    }

    bool operator!=(const Figure<T>& other) const override {
        return !(*this == other);
    }

    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Trapezoid<T>>(*this);
    }

    ~Trapezoid() override = default;
};

#endif
