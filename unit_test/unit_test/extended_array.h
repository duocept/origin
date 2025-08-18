#pragma once
#include <utility>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <typeinfo>
#include <type_traits>

template <typename T>
class ExtArray
{
private:
    std::vector<T> extended_array;
    size_t _size;
public:
    ExtArray(std::initializer_list<T> l) : extended_array(l), _size(l.size()) {}

    explicit ExtArray(int size) : _size(static_cast<size_t>(size)) {
        if (size < 0) throw std::invalid_argument("size < 0");
        extended_array.resize(_size);
    }

    T& operator[](size_t index) {
        return extended_array[index];
    }

    size_t size() { return _size; }

    // Задание 1: корректная работа с пустым массивом
    double mean() {
        if (_size == 0) return 0.0;
        double sum = 0.0;
        for (size_t i = 0; i < _size; ++i) sum += static_cast<double>(extended_array[i]);
        return sum / static_cast<double>(_size);
    }

    // Задание 2: перегрузка mean по диапазону [begin, end)
    double mean(size_t begin, size_t end) {
        if (begin >= end) throw std::invalid_argument("begin >= end");
        if (end > _size) throw std::out_of_range("range out of bounds");
        double sum = 0.0;
        for (size_t i = begin; i < end; ++i) sum += static_cast<double>(extended_array[i]);
        return sum / static_cast<double>(end - begin);
    }

    // Задание 1: корректная работа с пустым массивом
    double median() {
        if (_size == 0) return 0.0;
        std::vector<T> temp_array;
        temp_array.reserve(_size);
        std::copy(extended_array.begin(), extended_array.end(), std::back_inserter(temp_array));
        std::sort(temp_array.begin(), temp_array.end());
        if (_size % 2 == 1) {
            return static_cast<double>(temp_array[_size / 2]);
        }
        else {
            return (static_cast<double>(temp_array[(_size / 2) - 1]) +
                static_cast<double>(temp_array[_size / 2])) / 2.0;
        }
    }

    // Задание 1: корректная работа с пустым массивом
    std::pair<T, int> mode() {
        if (_size == 0) return { T{}, 0 };

        // Алгоритм: сортируем и считаем длины пробегов одинаковых значений
        std::vector<T> temp_array = extended_array;
        std::sort(temp_array.begin(), temp_array.end());

        T best_val = temp_array[0];
        int best_cnt = 1;

        T curr_val = temp_array[0];
        int curr_cnt = 1;

        for (size_t i = 1; i < _size; ++i) {
            if (temp_array[i] == curr_val) {
                ++curr_cnt;
            }
            else {
                if (curr_cnt > best_cnt) {
                    best_cnt = curr_cnt;
                    best_val = curr_val;
                }
                curr_val = temp_array[i];
                curr_cnt = 1;
            }
        }
        if (curr_cnt > best_cnt) {
            best_cnt = curr_cnt;
            best_val = curr_val;
        }
        return { best_val, best_cnt };
    }

    // Задание 3: checkSum
    std::size_t checkSum() {
        if constexpr (std::is_same_v<T, bool>) {
            std::size_t cnt = 0;
            for (auto v : extended_array) if (v) ++cnt;
            return cnt;
        }
        else if constexpr (std::is_same_v<T, int>) {
            std::size_t cnt = 0;
            for (auto v : extended_array) {
                if (v != 0 && v != 1) throw std::logic_error("int array contains values other than 0/1");
                if (v == 1) ++cnt;
            }
            return cnt;
        }
        else {
            throw std::bad_typeid();
        }
    }
};