#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <memory>
#include "Point.h"


template <Scalar T>
class Figure {
protected:
    Figure() = default;


    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual bool validate() const = 0;

public:
    virtual ~Figure() = default;

    virtual Point<T> center() const = 0;
    virtual double surface() const = 0;

    virtual operator double() const = 0;

    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual bool operator!=(const Figure<T>& other) const {
        return !(*this == other);
    }

    virtual std::shared_ptr<Figure<T>> clone() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        fig.print(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure<T>& fig) {
        fig.read(is);
        return is;
    }
};

#endif 
