#include "IsoscelesTriangle.h"
#include "GeometryError.h"

IsoscelesTriangle::IsoscelesTriangle(int a, int b, int A, int B)
    : Triangle(a, b, a, A, B, A)
{
    name = "Равнобедренный треугольник";
    if (!(a == c && A == C)) {
        throw GeometryError("в равнобедренном треугольнике должно быть a=c и A=C");
    }
}