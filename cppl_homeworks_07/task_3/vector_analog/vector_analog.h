#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;

    // Rule of five
    ~SimpleVector() { delete[] data_; }

    SimpleVector(const SimpleVector& other)
        : sz_(other.sz_), cap_(other.cap_),
        data_(other.cap_ ? new T[other.cap_] : nullptr) {
        for (std::size_t i = 0; i < sz_; ++i) data_[i] = other.data_[i];
    }

    SimpleVector& operator=(const SimpleVector& other) {
        if (this == &other) return *this;
        T* nd = other.cap_ ? new T[other.cap_] : nullptr;
        for (std::size_t i = 0; i < other.sz_; ++i) nd[i] = other.data_[i];
        delete[] data_;
        data_ = nd; sz_ = other.sz_; cap_ = other.cap_;
        return *this;
    }

    SimpleVector(SimpleVector&& other) noexcept
        : sz_(other.sz_), cap_(other.cap_), data_(other.data_) {
        other.sz_ = other.cap_ = 0; other.data_ = nullptr;
    }

    SimpleVector& operator=(SimpleVector&& other) noexcept {
        if (this == &other) return *this;
        delete[] data_;
        data_ = other.data_; sz_ = other.sz_; cap_ = other.cap_;
        other.data_ = nullptr; other.sz_ = other.cap_ = 0;
        return *this;
    }

    // Размер и ёмкость
    std::size_t size()     const noexcept { return sz_; }
    std::size_t capacity() const noexcept { return cap_; }
    bool        empty()    const noexcept { return sz_ == 0; }

    // Доступ к элементам
    T& at(std::size_t index) {
        if (index >= sz_) throw std::out_of_range("SimpleVector::at");
        return data_[index];
    }
    const T& at(std::size_t index) const {
        if (index >= sz_) throw std::out_of_range("SimpleVector::at");
        return data_[index];
    }

    // Не проверяет границы (как у std::vector)
    T& operator[](std::size_t index) noexcept { return data_[index]; }
    const T& operator[](std::size_t index) const noexcept { return data_[index]; }

    // Добавление в конец
    void push_back(const T& value) {
        ensure_capacity_for_push();
        data_[sz_++] = value;
    }
    void push_back(T&& value) {
        ensure_capacity_for_push();
        data_[sz_++] = std::move(value);
    }

    // Необязательные, но полезные
    void reserve(std::size_t new_cap) {
        if (new_cap > cap_) reallocate_(new_cap);
    }
    void clear() noexcept { sz_ = 0; } // данные не уничтожаются поэлементно — упрощение

private:
    std::size_t sz_ = 0;
    std::size_t cap_ = 0;
    T* data_ = nullptr;

    void ensure_capacity_for_push() {
        if (sz_ == cap_) reallocate_(cap_ ? cap_ * 2 : 1);
    }
    void reallocate_(std::size_t new_cap) {
        T* nd = new T[new_cap];                // упрощение: требует default-constructible T
        for (std::size_t i = 0; i < sz_; ++i)  // переносим/копируем старые элементы
            nd[i] = std::move(data_[i]);
        delete[] data_;
        data_ = nd;
        cap_ = new_cap;
    }
};