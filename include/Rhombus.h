#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"
#include "Point.h"
#include <array>
#include <memory>
#include <cmath>
#include <stdexcept>

template<Scalar T>
class Rhombus : public Figure<T> {
private:
    static constexpr int n = 4;
    std::array<std::unique_ptr<Point<T>>, n> vertices;

public:
    Rhombus() {
        for (auto& v : vertices)
            v = std::make_unique<Point<T>>();
    }

    Rhombus(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d) {
        vertices[0] = std::make_unique<Point<T>>(a);
        vertices[1] = std::make_unique<Point<T>>(b);
        vertices[2] = std::make_unique<Point<T>>(c);
        vertices[3] = std::make_unique<Point<T>>(d);
    }

    Rhombus(const Rhombus& other) {
        for (int i = 0; i < n; ++i)
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
    }

    Rhombus(Rhombus&& other) noexcept {
        for (int i = 0; i < n; ++i)
            vertices[i] = std::move(other.vertices[i]);
    }

    Rhombus& operator=(const Rhombus& other) {
        if (this == &other) return *this;
        for (int i = 0; i < n; ++i)
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        return *this;
    }

    Rhombus& operator=(Rhombus&& other) noexcept {
        if (this == &other) return *this;
        for (int i = 0; i < n; ++i)
            vertices[i] = std::move(other.vertices[i]);
        return *this;
    }

    void print(std::ostream& os) const override {
        os << "Rhombus: ";
        for (const auto& v : vertices)
            os << *v << " ";
    }

    void read(std::istream& is) override {
        for (auto& v : vertices)
            is >> *v;
        if (!validate())
            throw std::invalid_argument("Invalid rhombus: points do not form a valid shape.");
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
        const Rhombus<T>* o = dynamic_cast<const Rhombus<T>*>(&other);
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
        return std::make_shared<Rhombus<T>>(*this);
    }

    ~Rhombus() override = default;
};

#endif // RHOMBUS_H
