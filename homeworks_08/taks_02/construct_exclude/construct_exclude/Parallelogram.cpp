#include "Parallelogram.h"
#include "GeometryError.h"

Parallelogram::Parallelogram(int a, int b, int A, int B)
    : Quadrangle(a, b, a, b, A, B, A, B)
{
    name = "��������������";
    if (!(this->a == this->c && this->b == this->d)) {
        throw GeometryError("� ��������������� ������� ������� �����: a=c � b=d");
    }
    if (!(this->A == this->C && this->B == this->D)) {
        throw GeometryError("� ��������������� ���� ������� �����: A=C � B=D");
    }
}