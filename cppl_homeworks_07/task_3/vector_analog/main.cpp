#include <iostream>
#include <string>
#include "vector_analog.h"

int main() {
    SimpleVector<int> v;
    for (int i = 0; i < 5; ++i) v.push_back(i * i);

    std::cout << "size=" << v.size() << " cap=" << v.capacity() << "\n";
    for (std::size_t i = 0; i < v.size(); ++i) std::cout << v[i] << ' ';
    std::cout << "\n";

    try { std::cout << "at(100)=" << v.at(100) << "\n"; }
    catch (const std::out_of_range& e) { std::cout << "caught: " << e.what() << "\n"; }

    SimpleVector<std::string> s;
    s.push_back("Hello");
    s.push_back(", ");
    s.push_back("world!");
    std::cout << s.at(0) << s.at(1) << s.at(2) << "\n";

    return 0;
}