#include <iostream>
#include "Quadrangle.h"
#include "GeometryError.h"

Quadrangle::Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D)
    : Figure("��������������"), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D)
{
    if (a <= 0 || b <= 0 || c <= 0 || d <= 0) {
        throw GeometryError("������� ��������������� ������ ���� ��������������");
    }
    if (A + B + C + D != 360) {
        throw GeometryError("����� ����� ��������������� �� ����� 360");
    }
}

void Quadrangle::print_info() const {
    std::cout << name << ":\n";
    std::cout << "�������: a=" << a << " b=" << b << " c=" << c << " d=" << d << std::endl;
    std::cout << "����: A=" << A << " B=" << B << " C=" << C << " D=" << D << std::endl << std::endl;
}