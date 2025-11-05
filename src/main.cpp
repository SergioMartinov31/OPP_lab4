#include <iostream>
#include <memory>
#include <iomanip>
#include <array>

#include "Array.h"
#include "Trapezoid.h"
#include "Rhombus.h"
#include "Pentagon.h"

template <typename T>
std::string typeName(const Figure<T>& f) {
    if (dynamic_cast<const Trapezoid<T>*>(&f)) return "Trapezoid";
    if (dynamic_cast<const Rhombus<T>*>(&f)) return "Rhombus";
    if (dynamic_cast<const Pentagon<T>*>(&f)) return "Pentagon";
    return "Unknown Figure";
}

// Ввод координат для фигур
template <typename T>
void inputFigures(Array<std::shared_ptr<Figure<T>>>& figures) {
    for (size_t i = 0; i < figures.getSize(); ++i) {
        std::cout << "Figure " << i << " (" << typeName(*figures[i]) << "): ";
        std::cin >> *figures[i];
    }
}

// Вывод фигур и их площадей
template <typename T>
void printFigures(const Array<std::shared_ptr<Figure<T>>>& figures) {
    for (size_t i = 0; i < figures.getSize(); ++i)
        std::cout << i << ": " << typeName(*figures[i])
                  << " | Surface = " << double(*figures[i]) << "\n";
}

// Вывод центров
template <typename T>
void printCenters(const Array<std::shared_ptr<Figure<T>>>& figures) {
    for (size_t i = 0; i < figures.getSize(); ++i) {
        auto c = figures[i]->center();
        std::cout << i << ": (" << c.x << ", " << c.y << ")\n";
    }
}

int main() {
    using I = int;
    std::cout << std::fixed << std::setprecision(2);

    // ===========================
    // Полиморфный контейнер
    // ===========================
    Array<std::shared_ptr<Figure<I>>> figures;

    figures.add(std::make_shared<Trapezoid<I>>(Point<I>(0,0), Point<I>(4,0), Point<I>(3,2), Point<I>(0,2)));
    figures.add(std::make_shared<Rhombus<I>>(Point<I>(0,0), Point<I>(1,1), Point<I>(2,0), Point<I>(1,-1)));
    figures.add(std::make_shared<Pentagon<I>>(std::array<Point<I>,5>{Point<I>(0,0), Point<I>(1,0), Point<I>(2,1), Point<I>(1,2), Point<I>(0,1)}));

    std::cout << "\n=== Input vertex coordinates for polymorphic figures ===\n";
    inputFigures(figures);

    std::cout << "\n=== Polymorphic figures ===\n";
    printFigures(figures);

    std::cout << "\nCenters:\n";
    printCenters(figures);

    std::cout << "\nTotal surface = " << figures.totalSurface() << "\n";

    // ===========================
    // Тест копирования и перемещения (Trapezoid)
    // ===========================
    std::cout << "\n=== Copy & Move test (Trapezoid) ===\n";
    Trapezoid<I> t1(Point<I>(0,0), Point<I>(4,0), Point<I>(3,2), Point<I>(0,2));
    Trapezoid<I> t2 = t1;
    Trapezoid<I> t3 = std::move(t1);

    std::cout << "After copy (t2): " << t2 << "\n";
    std::cout << "After move (t3): " << t3 << "\n";

    // ===========================
    // Удаление первой фигуры
    // ===========================
    figures.remove(0);
    std::cout << "\nAfter removing first figure:\n";
    printFigures(figures);

    // ===========================
    // Неполиморфный контейнер
    // ===========================
    Array<Trapezoid<I>> trapezoids;
    trapezoids.add(Trapezoid<I>(Point<I>(0,0), Point<I>(4,0), Point<I>(3,2), Point<I>(0,2)));
    trapezoids.add(Trapezoid<I>(Point<I>(1,1), Point<I>(5,1), Point<I>(4,3), Point<I>(1,3)));

    std::cout << "\n=== Non-polymorphic container (Trapezoids) ===\n";
    for (size_t i = 0; i < trapezoids.getSize(); ++i) {
        auto c = trapezoids[i].center();
        std::cout << "Trapezoid " << i << " | Surface = " << double(trapezoids[i])
                  << " | Center = (" << c.x << ", " << c.y << ")\n";
    }

    trapezoids.remove(0);
    std::cout << "\nAfter removal, size = " << trapezoids.getSize() << "\n";

    // ===========================
    // Проверка выхода за пределы массива
    // ===========================
    try {
        std::cout << trapezoids[10];
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << "\n";
    }

    return 0;
}
