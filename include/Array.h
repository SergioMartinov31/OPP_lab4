#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <memory>
#include <stdexcept>
#include <iomanip>
#include <type_traits>

template<typename T>
class Array {
public:
    Array() : size_(0), capacity_(4) {
        data_ = std::make_shared<T[]>(capacity_);
    }

    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;
    ~Array() = default;

    // === Добавление элемента ===
    // 1) Для shared_ptr, если T — указатель
    void add(std::shared_ptr<typename std::remove_pointer<T>::type> elem) {
        if (size_ >= capacity_) resize();
        data_[size_++] = std::move(elem);
    }

    // 2) Для обычных объектов
    template <class U = T>
    std::enable_if_t<!std::is_pointer_v<U>> add(const U& elem) {
        if (size_ >= capacity_) resize();
        data_[size_++] = elem;
    }

    // 3) Для перемещения объектов
    template <class U = T>
    std::enable_if_t<!std::is_pointer_v<U>> add(U&& elem) {
        if (size_ >= capacity_) resize();
        data_[size_++] = std::move(elem);
    }

    // === Удаление по индексу ===
    void remove(size_t index) {
        if (index >= size_) throw std::out_of_range("Invalid index");
        for (size_t i = index; i + 1 < size_; ++i)
            data_[i] = std::move(data_[i + 1]);
        --size_;
    }

    // === Доступ к элементу ===
    T& operator[](size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    // === Печать площадей ===
    void printSurfaces() const {
        std::cout << std::fixed << std::setprecision(4);
        for (size_t i = 0; i < size_; ++i) {
            if constexpr (requires { double(data_[i]); }) {
                std::cout << i << ": " << data_[i]
                          << " | Area = " << double(data_[i]) << std::endl;
            } else if constexpr (requires { double(*data_[i]); }) {
                std::cout << i << ": " << *data_[i]
                          << " | Area = " << double(*data_[i]) << std::endl;
            }
        }
    }

    // === Печать центров ===
    void printCenters() const {
        for (size_t i = 0; i < size_; ++i) {
            if constexpr (requires { data_[i].center(); }) {
                auto c = data_[i].center();
                std::cout << i << ": Center = (" << c.x << ", " << c.y << ")" << std::endl;
            } else if constexpr (requires { data_[i]->center(); }) {
                auto c = data_[i]->center();
                std::cout << i << ": Center = (" << c.x << ", " << c.y << ")" << std::endl;
            }
        }
    }

    // === Общая площадь ===
    double totalSurface() const {
        double total = 0;
        for (size_t i = 0; i < size_; ++i) {
            if constexpr (requires { double(data_[i]); }) {
                total += double(data_[i]);
            } else if constexpr (requires { double(*data_[i]); }) {
                total += double(*data_[i]);
            }
        }
        return total;
    }

    // === Служебные методы ===
    size_t getSize() const { return size_; }
    size_t getCapacity() const { return capacity_; }

private:
    void resize() {
        capacity_ *= 2;
        auto newData = std::make_shared<T[]>(capacity_);
        for (size_t i = 0; i < size_; ++i)
            newData[i] = std::move(data_[i]);
        data_ = std::move(newData);
    }

    std::shared_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;
};

#endif // ARRAY_H
