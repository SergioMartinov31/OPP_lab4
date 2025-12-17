#include <iostream>
#include <memory>
#include <iomanip>
#include <array>
#include <string>

#include "Array.h"
#include "Trapezoid.h"
#include "Rhombus.h"
#include "Pentagon.h"

// Трапеция:       0 0   4 0   3 2   1 2
// Ромб:           0 0   2 1   4 0   2 -1
// Пятиугольник:   0 0   1 0   2 1   1 2   0 1

template <typename T>
std::string typeName(const Figure<T>& f) {
    if (dynamic_cast<const Trapezoid<T>*>(&f)) return "Trapezoid";
    if (dynamic_cast<const Rhombus<T>*>(&f))   return "Rhombus";
    if (dynamic_cast<const Pentagon<T>*>(&f))  return "Pentagon";
    return "Unknown Figure";
}

int main() {
    using I = int;
    std::cout << std::fixed << std::setprecision(2);

    /* ================= Polymorphic container ================= */

    Array<std::shared_ptr<Figure<I>>> figures;

    auto t = std::make_shared<Trapezoid<I>>(
        Point<I>(0, 0), Point<I>(4, 0), Point<I>(3, 2), Point<I>(0, 2)
    );

    auto r = std::make_shared<Rhombus<I>>(
        Point<I>(0, 0), Point<I>(1, 1), Point<I>(2, 0), Point<I>(1, -1)
    );

    std::array<Point<I>, 5> pentpts = {
        Point<I>(0, 0), Point<I>(1, 0), Point<I>(2, 1),
        Point<I>(1, 2), Point<I>(0, 1)
    };

    auto p = std::make_shared<Pentagon<I>>(pentpts);

    figures.add(t);
    figures.add(r);
    figures.add(p);

    std::cout << "\n=== Input vertex coordinates for polymorphic figures ===\n";
    for (size_t i = 0; i < figures.getSize(); ++i) {
        std::cout << "\nFigure " << i << " (" << typeName(*figures[i]) << "):\n";
        std::cin >> *figures[i];
    }

    std::cout << "\n=== List of polymorphic figures ===\n";
    figures.printAll();

    std::cout << "\n=== Centers ===\n";
    figures.printCenters();

    std::cout << "\n=== Total surface of all figures ===\n";
    figures.printTotalArea();

    /* ================= Copy & Move ================= */

    std::cout << "\n=== Copy & Move test (Trapezoid) ===\n";

    Trapezoid<I> t1(
        Point<I>(0, 0), Point<I>(4, 0), Point<I>(3, 2), Point<I>(0, 2)
    );

    std::cout << "Original:\n" << t1 << "\n";

    Trapezoid<I> t2 = t1;
    std::cout << "After copy:\n" << t2 << "\n";

    Trapezoid<I> t3 = std::move(t1);
    std::cout << "After move:\n" << t3 << "\n";

    /* ================= Remove from polymorphic ================= */

    std::cout << "\n=== Removing first figure ===\n";
    figures.remove(0);
    figures.printAll();

    /* ================= Non-polymorphic container ================= */

    Array<Trapezoid<I>> trapezoids;

    trapezoids.add(
        Trapezoid<I>(Point<I>(0, 0), Point<I>(4, 0), Point<I>(3, 2), Point<I>(0, 2))
    );

    trapezoids.add(
        Trapezoid<I>(Point<I>(1, 1), Point<I>(5, 1), Point<I>(4, 3), Point<I>(1, 3))
    );

    std::cout << "\n=== Non-polymorphic container (Trapezoids) ===\n";
    for (size_t i = 0; i < trapezoids.getSize(); ++i) {
        auto c = trapezoids[i].center();
        std::cout << "Trapezoid " << i
                  << " | Surface = " << double(trapezoids[i])
                  << " | Center = (" << c.x() << ", " << c.y() << ")\n";
    }

    std::cout << "\nRemoving first trapezoid...\n";
    trapezoids.remove(0);
    std::cout << "Size after removal = " << trapezoids.getSize() << "\n";

    /* ================= Out of range test ================= */

    std::cout << "\n=== Index out of bounds test ===\n";
    try {
        std::cout << trapezoids[10];
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << "\n";
    }

    return 0;
}
