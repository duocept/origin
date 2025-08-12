#include "Rhombus.h"
#include "GeometryError.h"

Rhombus::Rhombus(int a, int A, int B)
    : Parallelogram(a, a, A, B)
{
    name = "Ромб";
    if (!(this->a == this->b && this->b == this->c && this->c == this->d)) {
        throw GeometryError("в ромбе все стороны должны быть равны");
    }
    if (!(this->A == this->C && this->B == this->D)) {
        throw GeometryError("в ромбе углы попарно равны: A=C и B=D");
    }
}