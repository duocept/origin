#include "Parallelogram.h"
#include "GeometryError.h"

Parallelogram::Parallelogram(int a, int b, int A, int B)
    : Quadrangle(a, b, a, b, A, B, A, B)
{
    name = "Параллелограмм";
    if (!(this->a == this->c && this->b == this->d)) {
        throw GeometryError("в параллелограмме стороны попарно равны: a=c и b=d");
    }
    if (!(this->A == this->C && this->B == this->D)) {
        throw GeometryError("в параллелограмме углы попарно равны: A=C и B=D");
    }
}