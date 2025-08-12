#include "EquilateralTriangle.h"
#include "GeometryError.h"

EquilateralTriangle::EquilateralTriangle(int a)
    : Triangle(a, a, a, 60, 60, 60)
{
    name = "�������������� �����������";
    if (!(a == b && b == c)) {
        throw GeometryError("� �������������� ������������ ��� ������� ������ ���� �����");
    }
    if (!(A == 60 && B == 60 && C == 60)) {
        throw GeometryError("� �������������� ������������ ��� ���� ������ ���� 60");
    }
}