﻿#include <iostream>

#define SUB(a, b) ((a) - (b))

int main() {
    int a = 6;
    int b = 5;
    int c = 2;

    std::cout << SUB(a, b) << std::endl;           // ((6) - (5)) = 1
    std::cout << SUB(a, b) * c << std::endl;       // ((6) - (5)) * 2 = 2
    std::cout << SUB(a, b + c) * c << std::endl;   // ((6) - (5 + 2)) * 2 = (-1) * 2 = -2

    return EXIT_SUCCESS;
}