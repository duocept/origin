#include "RectangleQ.h"

RectangleQ::RectangleQ(int a, int b)
    : Quadrangle(a, b, a, b, 90, 90, 90, 90) {
    name = "Прямоугольник";
}