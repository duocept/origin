#pragma once
#include <vector>
#include <type_traits>

// Шаблон для скалярных типов (число → число)
template <typename T>
auto square(const T& x) -> decltype(x* x) {
    return x * x;
}

// Шаблон-перегрузка для векторов (покоординатно)
template <typename T>
std::vector<T> square(const std::vector<T>& v) {
    std::vector<T> out;
    out.reserve(v.size());
    for (const auto& el : v) {
        out.push_back(square(el)); // использует вариант выше для элемента
    }
    return out;
}