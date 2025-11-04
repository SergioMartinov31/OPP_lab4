#include <iostream>
#include <memory>
#include "Point.h"
#include "Figure.h"
#include "Array.h"
#include "Trapezoid.h"
#include "Rhombus.h"
#include "Pentagon.h"


int main() {
    using I = int;

    Array< Figure<I> > arr;

    auto t = std::make_shared< Trapezoid<I> >(
        Point<I>(0, 0),
        Point<I>(4, 0),
        Point<I>(3, 2),
        Point<I>(0, 2)
    );

    auto r = std::make_shared< Rhombus<I> >(
        Point<I>(0, 0),
        Point<I>(1, 1),
        Point<I>(2, 0),
        Point<I>(1, -1)
    );

    std::array<Point<I>, 5> pentpts = {
        Point<I>(0, 0),
        Point<I>(1, 0),
        Point<I>(2, 1),
        Point<I>(1, 2),
        Point<I>(0, 1)
    };
    auto p = std::make_shared< Pentagon<I> >(pentpts);

    arr.add(std::static_pointer_cast<Figure<I>>(t));
    arr.add(std::static_pointer_cast<Figure<I>>(r));
    arr.add(std::static_pointer_cast<Figure<I>>(p));

    std::cout << "All figures:\n";
    arr.printSurfaces();

    std::cout << "\nCenters:\n";
    arr.printCenters();

    std::cout << "\nTotal surface = " << arr.totalSurface() << std::endl;

    std::cout << "\nRemoving index 1 (rhombus)...\n";
    arr.remove(1);

    arr.printSurfaces();
    std::cout << "Total surface = " << arr.totalSurface() << std::endl;

    return 0;
}
