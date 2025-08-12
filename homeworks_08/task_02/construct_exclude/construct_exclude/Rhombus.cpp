#include "Rhombus.h"
#include "GeometryError.h"

Rhombus::Rhombus(int a, int A, int B)
    : Parallelogram(a, a, A, B)
{
    name = "����";
    if (!(this->a == this->b && this->b == this->c && this->c == this->d)) {
        throw GeometryError("� ����� ��� ������� ������ ���� �����");
    }
    if (!(this->A == this->C && this->B == this->D)) {
        throw GeometryError("� ����� ���� ������� �����: A=C � B=D");
    }
}