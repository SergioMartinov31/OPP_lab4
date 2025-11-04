#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Figure.h"
#include <array>
#include <cmath>

template<typename T>
class Trapezoid : public Figure<T> {
public:
    Trapezoid() {
        for (auto &p : pts) p = std::make_unique<Point<T>>();
    }

    Trapezoid(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d) {
        pts[0] = std::make_unique<Point<T>>(a);
        pts[1] = std::make_unique<Point<T>>(b);
        pts[2] = std::make_unique<Point<T>>(c);
        pts[3] = std::make_unique<Point<T>>(d);
    }

    Trapezoid(const Trapezoid& other) {
        for (size_t i = 0; i < 4; ++i)
            pts[i] = std::make_unique<Point<T>>(*other.pts[i]);
    }

    Trapezoid(Trapezoid&& other) noexcept {
        for (size_t i = 0; i < 4; ++i)
            pts[i] = std::move(other.pts[i]);
    }

    Trapezoid& operator=(const Trapezoid& other) {
        if (this == &other) return *this;
        for (size_t i = 0; i < 4; ++i)
            pts[i] = std::make_unique<Point<T>>(*other.pts[i]);
        return *this;
    }

    Trapezoid& operator=(Trapezoid&& other) noexcept {
        if (this == &other) return *this;
        for (size_t i = 0; i < 4; ++i)
            pts[i] = std::move(other.pts[i]);
        return *this;
    }

    void print(std::ostream& os) const noexcept override {
        os << "Trapezoid: ";
        for (int i = 0; i < 4; ++i)
            os << *pts[i] << " ";
    }

    void read(std::istream& is) override {
        for (int i = 0; i < 4; ++i) {
            Point<T> tmp; is >> tmp;
            pts[i] = std::make_unique<Point<T>>(tmp);
        }
    }

    bool validate() const override {
        for (int i = 0; i < 4; ++i)
            for (int j = i + 1; j < 4; ++j)
                if (pts[i]->x == pts[j]->x && pts[i]->y == pts[j]->y)
                    return false;
        return surface() > 1e-12;
    }

    Point<T> center() const override {
        long double sx = 0, sy = 0;
        for (int i = 0; i < 4; ++i) {
            sx += pts[i]->x;
            sy += pts[i]->y;
        }
        return Point<T>((T)(sx / 4.0L), (T)(sy / 4.0L));
    }

    double surface() const override {
        long double s = 0;
        for (int i = 0; i < 4; ++i) {
            int j = (i + 1) % 4;
            s += (long double)pts[i]->x * (long double)pts[j]->y -
                 (long double)pts[j]->x * (long double)pts[i]->y;
        }
        return std::abs((double)(s / 2.0L));
    }

    operator double() const override { return surface(); }

    bool operator==(const Figure<T>& other) const override {
        if (typeid(*this) != typeid(other)) return false;
        auto& o = static_cast<const Trapezoid<T>&>(other);
        for (int i = 0; i < 4; ++i)
            if (pts[i]->x != o.pts[i]->x || pts[i]->y != o.pts[i]->y)
                return false;
        return true;
    }

    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Trapezoid<T>>(*this);
    }

private:
    std::array<std::unique_ptr<Point<T>>, 4> pts;
};

#endif // TRAPEZOID_H
