#include "EquilateralTriangle.h"
#include "GeometryError.h"

EquilateralTriangle::EquilateralTriangle(int a)
    : Triangle(a, a, a, 60, 60, 60)
{
    name = "–авносторонний треугольник";
    if (!(a == b && b == c)) {
        throw GeometryError("в равностороннем треугольнике все стороны должны быть равны");
    }
    if (!(A == 60 && B == 60 && C == 60)) {
        throw GeometryError("в равностороннем треугольнике все углы должны быть 60");
    }
}