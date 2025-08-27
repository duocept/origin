#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

int main() {
    std::cout << "[IN]: ";
    std::string s;
    std::getline(std::cin, s);

    // Подсчёт частот + запоминаем первую позицию появления (на случай тай-брейка)
    std::unordered_map<char, std::size_t> freq, first_pos;
    for (std::size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        ++freq[c];
        if (!first_pos.count(c)) first_pos[c] = i;
    }

    // Переносим в вектор для сортировки
    std::vector<std::pair<char, std::size_t>> items(freq.begin(), freq.end());

    // Сортировка: частота по убыванию, при равенстве — по символу (можно сменить правило ниже)
    std::stable_sort(items.begin(), items.end(),
        [&](const auto& a, const auto& b) {
            if (a.second != b.second) return a.second > b.second; // выше частота — раньше
    return a.first < b.first;                              // тай-брейк: символ по возрастанию
    // Если нужно сохранять порядок первого появления:
    // return first_pos.at(a.first) < first_pos.at(b.first);
        });

    std::cout << "[OUT]:\n";
    for (const auto& [ch, cnt] : items) {
        std::cout << ch << ": " << cnt << '\n';
    }
    return 0;
}