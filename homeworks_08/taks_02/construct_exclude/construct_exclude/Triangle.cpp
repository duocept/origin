#include <iostream>
#include "Triangle.h"
#include "GeometryError.h"

Triangle::Triangle(int a, int b, int c, int A, int B, int C)
    : Figure("�����������"), a(a), b(b), c(c), A(A), B(B), C(C)
{
    if (a <= 0 || b <= 0 || c <= 0) {
        throw GeometryError("������� ������������ ������ ���� ��������������");
    }
    if (A + B + C != 180) {
        throw GeometryError("����� ����� ������������ �� ����� 180");
    }
    if (!(a + b > c && a + c > b && b + c > a)) {
        throw GeometryError("�������� ����������� �����������");
    }
}

void Triangle::print_info() const {
    std::cout << name << ":\n";
    std::cout << "�������: a=" << a << " b=" << b << " c=" << c << std::endl;
    std::cout << "����: A=" << A << " B=" << B << " C=" << C << std::endl << std::endl;
}