#include "RectangleQ.h"
#include "GeometryError.h"

RectangleQ::RectangleQ(int a, int b)
    : Quadrangle(a, b, a, b, 90, 90, 90, 90)
{
    name = "Прямоугольник";
    if (!(a == c && b == d)) {
        throw GeometryError("в прямоугольнике стороны попарно равны: a=c и b=d");
    }
    if (!(A == 90 && B == 90 && C == 90 && D == 90)) {
        throw GeometryError("в прямоугольнике все углы должны быть 90");
    }
}