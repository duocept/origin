#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>

template <class T>
void make_unique_sorted(std::vector<T>& v) {
    std::sort(v.begin(), v.end());                    // сортируем
    v.erase(std::unique(v.begin(), v.end()), v.end()); // убираем дубли
}

int main() {
    std::cout << "[IN]: ";
    std::string line;
    std::getline(std::cin, line);

    std::istringstream iss(line);
    std::vector<int> v{ std::istream_iterator<int>(iss), std::istream_iterator<int>() };

    make_unique_sorted(v);

    std::cout << "[OUT]: ";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << (i + 1 == v.size() ? '\n' : ' ');
    }
    return 0;
}