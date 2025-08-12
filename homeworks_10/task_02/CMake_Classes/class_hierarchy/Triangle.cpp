#include <iostream>
#include "Triangle.h"

Triangle::Triangle(int a, int b, int c, int A, int B, int C)
    : Figure("�����������"), a(a), b(b), c(c), A(A), B(B), C(C) {}

void Triangle::print_info() const {
    std::cout << name << ":\n";
    std::cout << "�������: a=" << a << " b=" << b << " c=" << c << std::endl;
    std::cout << "����: A=" << A << " B=" << B << " C=" << C << std::endl << std::endl;
}