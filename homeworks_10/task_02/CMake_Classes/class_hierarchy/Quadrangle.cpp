#include <iostream>
#include "Quadrangle.h"

Quadrangle::Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D)
    : Figure("��������������"), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {}
void Quadrangle::print_info() const {
    std::cout << name << ":\n";
    std::cout << "�������: a=" << a << " b=" << b << " c=" << c << " d=" << d << std::endl;
    std::cout << "����: A=" << A << " B=" << B << " C=" << C << " D=" << D << std::endl << std::endl;
}