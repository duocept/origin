#include <iostream>
#include "Triangle.h"
#include "GeometryError.h"

Triangle::Triangle(int a, int b, int c, int A, int B, int C)
    : Figure("Треугольник"), a(a), b(b), c(c), A(A), B(B), C(C)
{
    if (a <= 0 || b <= 0 || c <= 0) {
        throw GeometryError("стороны треугольника должны быть положительными");
    }
    if (A + B + C != 180) {
        throw GeometryError("сумма углов треугольника не равна 180");
    }
    if (!(a + b > c && a + c > b && b + c > a)) {
        throw GeometryError("нарушено треугольное неравенство");
    }
}

void Triangle::print_info() const {
    std::cout << name << ":\n";
    std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << std::endl;
    std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << std::endl << std::endl;
}