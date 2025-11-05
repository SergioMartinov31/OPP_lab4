#include <iostream>
#include <memory>
#include <iomanip>
#include <string>

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

    // Создаём фигуры
    auto t = std::make_shared<Trapezoid<I>>(
        Point<I>(0, 0), Point<I>(4, 0),
        Point<I>(3, 2), Point<I>(0, 2)
    );

    auto r = std::make_shared<Rhombus<I>>(
        Point<I>(0, 0), Point<I>(1, 1),
        Point<I>(2, 0), Point<I>(1, -1)
    );

    std::array<Point<I>, 5> pentpts = {
        Point<I>(0, 0), Point<I>(1, 0),
        Point<I>(2, 1), Point<I>(1, 2),
        Point<I>(0, 1)
    };
    auto p = std::make_shared<Pentagon<I>>(pentpts);

    // Добавляем фигуры в массив
    figures.add(t);
    figures.add(r);
    figures.add(p);

    // ===========================
    // Ввод координат
    // ===========================
    std::cout << "\n=== Input of vertex coordinates ===\n";
    for (size_t i = 0; i < figures.getSize(); ++i) {
        std::cout << "Figure " << i << " - " << typeName(*figures[i]) << ":\n";
        std::cin >> *figures[i];
    }

    // ===========================
    // Вывод фигур и площадей
    // ===========================
    std::cout << "\n=== List of figures ===\n";
    for (size_t i = 0; i < figures.getSize(); ++i) {
        std::cout << i << ": " << typeName(*figures[i])
                  << " | Surface = " << double(*figures[i]) << "\n";
    }

    // ===========================
    // Центры фигур
    // ===========================
    std::cout << "\n=== Geometric centers ===\n";
    for (size_t i = 0; i < figures.getSize(); ++i) {
        auto c = figures[i]->center();
        std::cout << i << ": Center = (" << c.x << ", " << c.y << ")\n";
    }

    // ===========================
    // Общая площадь
    // ===========================
    std::cout << "\n=== Total surface of all figures ===\n";
    std::cout << "Total surface = " << figures.totalSurface() << "\n";

    // ===========================
    // Проверка operator==
    // ===========================
    std::cout << "\n=== Operator== check ===\n";
    if (*figures[0] == *figures[1])
        std::cout << "Figure 0 is equal to Figure 1\n";
    else
        std::cout << "Figure 0 is NOT equal to Figure 1\n";

    // ===========================
    // Проверка copy & move
    // ===========================
    std::cout << "\n=== Copy & move test (Trapezoid) ===\n";
    Trapezoid<I> t1 = *std::dynamic_pointer_cast<Trapezoid<I>>(figures[0]);
    std::cout << "Original trapezoid:\n" << t1 << "\n";

    Trapezoid<I> t2 = t1;
    std::cout << "After copy (t2):\n" << t2 << "\n";

    Trapezoid<I> t3 = std::move(t1);
    std::cout << "After move (t3):\n" << t3 << "\n";

    // ===========================
    // Удаление фигуры
    // ===========================
    std::cout << "\n=== Removing Figure 1 (Rhombus) ===\n";
    figures.remove(1);

    std::cout << "Figures after removal:\n";
    for (size_t i = 0; i < figures.getSize(); ++i)
        std::cout << i << ": " << typeName(*figures[i])
                  << " | Surface = " << double(*figures[i]) << "\n";

    // ===========================
    // Проверка исключений
    // ===========================
    std::cout << "\n=== Testing array index out of bounds ===\n";
    try {
        std::cout << figures[10];
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << "\n";
    }

    return 0;
}
