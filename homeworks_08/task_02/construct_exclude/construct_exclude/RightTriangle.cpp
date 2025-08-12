#include "RightTriangle.h"
#include "GeometryError.h"

RightTriangle::RightTriangle(int a, int b, int c, int A, int B)
    : Triangle(a, b, c, A, B, 90)
{
    name = "������������� �����������";
    if (C != 90) {
        throw GeometryError("� ������������� ������������ ���� C ������ ���� 90");
    }
}