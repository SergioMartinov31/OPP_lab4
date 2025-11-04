#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <iostream>
#include <stdexcept>
#include <iomanip>

template<typename T>
class Array {
public:
    Array() : size_(0), capacity_(4) {
        data_ = std::make_unique<std::shared_ptr<T>[]>(capacity_);
    }

    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

    void add(std::shared_ptr<T> elem) {
        if (size_ >= capacity_) resize();
        data_[size_++] = std::move(elem);
    }

    void remove(size_t index) {
        if (index >= size_) throw std::out_of_range("Invalid index");
        data_[index].reset();
        for (size_t i = index; i + 1 < size_; ++i)
            data_[i] = std::move(data_[i + 1]);
        data_[--size_].reset();
    }

    std::shared_ptr<T>& operator[](size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    const std::shared_ptr<T>& operator[](size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    void printSurfaces() const {
        std::cout << std::fixed << std::setprecision(4);
        for (size_t i = 0; i < size_; ++i)
            std::cout << i << ": " << *data_[i] << " | Area = " << static_cast<double>(*data_[i]) << std::endl;
    }

    void printCenters() const {
        for (size_t i = 0; i < size_; ++i) {
            auto c = data_[i]->center();
            std::cout << i << ": Center = (" << c.x << ", " << c.y << ")" << std::endl;
        }
    }

    double totalSurface() const {
        double total = 0;
        for (size_t i = 0; i < size_; ++i)
            total += static_cast<double>(*data_[i]);
        return total;
    }

    size_t getSize() const { return size_; }

private:
    void resize() {
        capacity_ *= 2;
        auto newData = std::make_unique<std::shared_ptr<T>[]>(capacity_);
        for (size_t i = 0; i < size_; ++i)
            newData[i] = std::move(data_[i]);
        data_ = std::move(newData);
    }

    std::unique_ptr<std::shared_ptr<T>[]> data_;
    size_t size_;
    size_t capacity_;
};

#endif // ARRAY_H
