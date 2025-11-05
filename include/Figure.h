#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <memory>
#include "Point.h"

// Базовый абстрактный класс для всех фигур
template <Scalar T>
class Figure {
protected:
    Figure() = default;

    // Эти методы должны быть переопределены в наследниках,
    // но не должны вызываться напрямую пользователем
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual bool validate() const = 0;

public:
    virtual ~Figure() = default;

    // Геометрические операции
    virtual Point<T> center() const = 0;
    virtual double surface() const = 0;

    // Приведение к double — площадь
    virtual operator double() const = 0;

    // Сравнение фигур
    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual bool operator!=(const Figure<T>& other) const {
        return !(*this == other);
    }

    // Клонирование (глубокое копирование)
    virtual std::shared_ptr<Figure<T>> clone() const = 0;

    // Потоковые операторы
    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        fig.print(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure<T>& fig) {
        fig.read(is);
        return is;
    }
};

#endif // FIGURE_H
