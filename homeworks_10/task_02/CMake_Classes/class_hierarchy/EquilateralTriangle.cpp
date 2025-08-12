#include "EquilateralTriangle.h"

EquilateralTriangle::EquilateralTriangle(int a)
    : Triangle(a, a, a, 60, 60, 60) {
    name = "Равносторонний треугольник";
}