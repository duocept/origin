#include <iostream>
#include "table.h"

int main() {
    table<int> test(2, 3);
    test[0][0] = 4;
    std::cout << test[0][0] << '\n'; // выводит 4

    auto [rows, cols] = test.Size();
    std::cout << "Size: " << rows << "x" << cols << '\n'; // 2x3
    return 0;
}