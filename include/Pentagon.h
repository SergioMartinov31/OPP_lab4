#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"
#include <array>
#include <cmath>

template<typename T>
class Pentagon : public Figure<T> {
public:
    Pentagon() {
        for (auto &p : pts)
            p = std::make_unique<Point<T>>();
    }

    explicit Pentagon(const std::array<Point<T>, 5>& arr) {
        for (int i = 0; i < 5; ++i)
            pts[i] = std::make_unique<Point<T>>(arr[i]);
    }

    Pentagon(const Pentagon& other) {
        for (int i = 0; i < 5; ++i)
            pts[i] = std::make_unique<Point<T>>(*other.pts[i]);
    }

    Pentagon(Pentagon&& other) noexcept {
        for (int i = 0; i < 5; ++i)
            pts[i] = std::move(other.pts[i]);
    }

    Pentagon& operator=(const Pentagon& other) {
        if (this == &other) return *this;
        for (int i = 0; i < 5; ++i)
            pts[i] = std::make_unique<Point<T>>(*other.pts[i]);
        return *this;
    }

    Pentagon& operator=(Pentagon&& other) noexcept {
        if (this == &other) return *this;
        for (int i = 0; i < 5; ++i)
            pts[i] = std::move(other.pts[i]);
        return *this;
    }

    void print(std::ostream& os) const noexcept override {
        os << "Pentagon: ";
        for (int i = 0; i < 5; ++i)
            os << *pts[i] << " ";
    }

    void read(std::istream& is) override {
        for (int i = 0; i < 5; ++i) {
            Point<T> tmp;
            is >> tmp;
            pts[i] = std::make_unique<Point<T>>(tmp);
        }
    }

    bool validate() const override { return surface() > 1e-12; }

    Point<T> center() const override {
        long double sx = 0, sy = 0;
        for (int i = 0; i < 5; ++i) {
            sx += pts[i]->x;
            sy += pts[i]->y;
        }
        return Point<T>((T)(sx / 5.0L), (T)(sy / 5.0L));
    }

    double surface() const override {
        long double s = 0;
        for (int i = 0; i < 5; ++i) {
            int j = (i + 1) % 5;
            s += (long double)pts[i]->x * (long double)pts[j]->y -
                 (long double)pts[j]->x * (long double)pts[i]->y;
        }
        return std::abs((double)(s / 2.0L));
    }

    operator double() const override { return surface(); }

    bool operator==(const Figure<T>& other) const override {
        if (typeid(*this) != typeid(other)) return false;
        auto& o = static_cast<const Pentagon<T>&>(other);
        for (int i = 0; i < 5; ++i)
            if (pts[i]->x != o.pts[i]->x || pts[i]->y != o.pts[i]->y)
                return false;
        return true;
    }

    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Pentagon<T>>(*this);
    }

private:
    std::array<std::unique_ptr<Point<T>>, 5> pts;
};

#endif // PENTAGON_H
