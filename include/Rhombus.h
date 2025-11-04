#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"
#include <array>
#include <cmath>

template<typename T>
class Rhombus : public Figure<T> {
public:
    Rhombus() {
        for (auto &p : pts) p = std::make_unique<Point<T>>();
    }

    Rhombus(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d) {
        pts[0] = std::make_unique<Point<T>>(a);
        pts[1] = std::make_unique<Point<T>>(b);
        pts[2] = std::make_unique<Point<T>>(c);
        pts[3] = std::make_unique<Point<T>>(d);
    }

    Rhombus(const Rhombus& other) {
        for (int i = 0; i < 4; ++i)
            pts[i] = std::make_unique<Point<T>>(*other.pts[i]);
    }

    Rhombus(Rhombus&& other) noexcept {
        for (int i = 0; i < 4; ++i)
            pts[i] = std::move(other.pts[i]);
    }

    Rhombus& operator=(const Rhombus& other) {
        if (this == &other) return *this;
        for (int i = 0; i < 4; ++i)
            pts[i] = std::make_unique<Point<T>>(*other.pts[i]);
        return *this;
    }

    Rhombus& operator=(Rhombus&& other) noexcept {
        if (this == &other) return *this;
        for (int i = 0; i < 4; ++i)
            pts[i] = std::move(other.pts[i]);
        return *this;
    }

    void print(std::ostream& os) const override {
        os << "Rhombus: ";
        for (int i = 0; i < 4; ++i)
            os << *pts[i] << " ";
    }

    void read(std::istream& is) override {
        for (int i = 0; i < 4; ++i) {
            Point<T> tmp;
            is >> tmp;
            pts[i] = std::make_unique<Point<T>>(tmp);
        }
    }

    bool validate() const override { return surface() > 1e-12; }

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

    bool operator==(const Figure<T>& other) const noexcept override {
        if (typeid(*this) != typeid(other)) return false;
        auto& o = static_cast<const Rhombus<T>&>(other);
        for (int i = 0; i < 4; ++i)
            if (pts[i]->x != o.pts[i]->x || pts[i]->y != o.pts[i]->y)
                return false;
        return true;
    }

    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Rhombus<T>>(*this);
    }

private:
    std::array<std::unique_ptr<Point<T>>, 4> pts;
};

#endif // RHOMBUS_H
