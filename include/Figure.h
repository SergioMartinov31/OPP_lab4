#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <memory>
#include "Point.h"

template<Scalar T>
class Figure {
public:
    virtual ~Figure() = default;

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual bool validate() const = 0;
    virtual Point<T> center() const = 0;
    virtual double surface() const = 0;
    virtual operator double() const = 0;
    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual std::shared_ptr<Figure<T>> clone() const = 0;
};

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const Figure<T>& f) {
    f.print(os);
    return os;
}

template<typename T>
inline std::istream& operator>>(std::istream& is, Figure<T>& f) {
    f.read(is);
    return is;
}

#endif // FIGURE_H
