#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"
#include "Point.h"
#include <array>
#include <memory>
#include <cmath>
#include <stdexcept>

template<Scalar T>
class Pentagon : public Figure<T> {
private:
    static constexpr int n = 5;
    std::array<std::unique_ptr<Point<T>>, n> vertices;

public:
    Pentagon() {
        for (auto& v : vertices)
            v = std::make_unique<Point<T>>();
    }

    explicit Pentagon(const std::array<Point<T>, n>& arr) {
        for (int i = 0; i < n; ++i)
            vertices[i] = std::make_unique<Point<T>>(arr[i]);
    }

    Pentagon(const Pentagon& other) {
        for (int i = 0; i < n; ++i)
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
    }

    Pentagon(Pentagon&& other) noexcept {
        for (int i = 0; i < n; ++i)
            vertices[i] = std::move(other.vertices[i]);
    }

    Pentagon& operator=(const Pentagon& other) {
        if (this == &other) return *this;
        for (int i = 0; i < n; ++i)
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        return *this;
    }

    Pentagon& operator=(Pentagon&& other) noexcept {
        if (this == &other) return *this;
        for (int i = 0; i < n; ++i)
            vertices[i] = std::move(other.vertices[i]);
        return *this;
    }

    void print(std::ostream& os) const override {
        os << "Pentagon: ";
        for (const auto& v : vertices)
            os << *v << " ";
    }

    void read(std::istream& is) override {
        for (auto& v : vertices)
            is >> *v;
        if (!validate())
            throw std::invalid_argument("Invalid pentagon: points do not form a valid shape.");
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
        const Pentagon<T>* o = dynamic_cast<const Pentagon<T>*>(&other);
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
        return std::make_shared<Pentagon<T>>(*this);
    }

    ~Pentagon() override = default;
};

#endif // PENTAGON_H
