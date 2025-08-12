#include "IsoscelesTriangle.h"
#include "GeometryError.h"

IsoscelesTriangle::IsoscelesTriangle(int a, int b, int A, int B)
    : Triangle(a, b, a, A, B, A)
{
    name = "�������������� �����������";
    if (!(a == c && A == C)) {
        throw GeometryError("� �������������� ������������ ������ ���� a=c � A=C");
    }
}