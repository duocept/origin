#pragma once
#include <vector>
#include <utility>    // std::pair
#include <stdexcept>  // std::out_of_range

template <typename T>
class table {
public:
    using size_type = std::size_t;

    // Конструктор: rows — строки, cols — столбцы
    table(size_type rows, size_type cols)
        : data_(rows, std::vector<T>(cols)) {}

    // Неконстантная версия operator[]
    std::vector<T>& operator[](size_type row) {
        return data_.at(row); // проверка границ по строке
    }

    // Константная версия operator[]
    const std::vector<T>& operator[](size_type row) const {
        return data_.at(row); // проверка границ по строке
    }

    // Размер таблицы: (кол-во строк, кол-во столбцов)
    std::pair<size_type, size_type> Size() const noexcept {
        return { data_.size(), data_.empty() ? 0 : data_.front().size() };
    }

    // (Опционально) отдельные геттеры
    size_type Rows() const noexcept { return data_.size(); }
    size_type Cols() const noexcept { return data_.empty() ? 0 : data_.front().size(); }

private:
    std::vector<std::vector<T>> data_;
};