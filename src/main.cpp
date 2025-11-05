#include <iostream>
#include <memory>
#include <iomanip>
#include <string>
#include <array>

#include "Array.h"
#include "Trapezoid.h"
#include "Rhombus.h"
#include "Pentagon.h"

// Функция для определения типа фигуры
template <typename T>
std::string typeName(const Figure<T>& f) {
    if (dynamic_cast<const Trapezoid<T>*>(&f)) return "Trapezoid";
    if (dynamic_cast<const Rhombus<T>*>(&f)) return "Rhombus";
    if (dynamic_cast<const Pentagon<T>*>(&f)) return "Pentagon";
    return "Unknown Figure";
}

int main() {
    using I = int;
    std::cout << std::fixed << std::setprecision(2);

    // ===========================
    // Полиморфный контейнер
    // ===========================
    Array<std::shared_ptr<Figure<I>>> figures;

    auto t = std::make_shared<Trapezoid<I>>(Point<I>(0,0), Point<I>(4,0), Point<I>(3,2), Point<I>(0,2));
    auto r = std::make_shared<Rhombus<I>>(Point<I>(0,0), Point<I>(1,1), Point<I>(2,0), Point<I>(1,-1));
    std::array<Point<I>,5> pentpts = {Point<I>(0,0), Point<I>(1,0), Point<I>(2,1), Point<I>(1,2), Point<I>(0,1)};
    auto p = std::make_shared<Pentagon<I>>(pentpts);

    figures.add(t);
    figures.add(r);
    figures.add(p);

    std::cout << "\n=== Input of vertex coordinates (polymorphic) ===\n";
    for (size_t i = 0; i < figures.getSize(); ++i) {
        std::cout << "Figure " << i << " - " << typeName(*figures[i]) << ":\n";
        std::cin >> *figures[i];
    }

    std::cout << "\n=== Polymorphic figures ===\n";
    for (size_t i = 0; i < figures.getSize(); ++i)
        std::cout << i << ": " << typeName(*figures[i]) << " | Surface = " << double(*figures[i]) << "\n";

    std::cout << "\nCenters:\n";
    for (size_t i = 0; i < figures.getSize(); ++i) {
        auto c = figures[i]->center();
        std::cout << i << ": (" << c.x << ", " << c.y << ")\n";
    }

    std::cout << "\nTotal surface = " << figures.totalSurface() << "\n";

    // ===========================
    // Неполиморфный контейнер
    // ===========================
    Array<Trapezoid<I>> trapezoids;
    trapezoids.add(Trapezoid<I>(Point<I>(0,0), Point<I>(4,0), Point<I>(3,2), Point<I>(0,2)));
    trapezoids.add(Trapezoid<I>(Point<I>(1,1), Point<I>(5,1), Point<I>(4,3), Point<I>(1,3)));

    std::cout << "\n=== Non-polymorphic container (Trapezoids) ===\n";
    for (size_t i = 0; i < trapezoids.getSize(); ++i) {
        std::cout << "Trapezoid " << i << " | Surface = " << double(trapezoids[i]) << "\n";
        auto c = trapezoids[i].center();
        std::cout << "Center = (" << c.x << ", " << c.y << ")\n";
    }

    std::cout << "\nRemoving first trapezoid...\n";
    trapezoids.remove(0);
    std::cout << "After removal, size = " << trapezoids.getSize() << "\n";

    return 0;
}
