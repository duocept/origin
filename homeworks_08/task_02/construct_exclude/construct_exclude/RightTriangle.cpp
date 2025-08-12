#include "RightTriangle.h"
#include "GeometryError.h"

RightTriangle::RightTriangle(int a, int b, int c, int A, int B)
    : Triangle(a, b, c, A, B, 90)
{
    name = "Прямоугольный треугольник";
    if (C != 90) {
        throw GeometryError("в прямоугольном треугольнике угол C должен быть 90");
    }
}