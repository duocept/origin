#include "Square.h"
#include "GeometryError.h"

Square::Square(int a)
    : RectangleQ(a, a)
{
    name = "�������";
    // � RectangleQ ��� ���������� a=c � b=d; ����� �������� ��������� ���� ������
    if (!(this->a == this->b && this->b == this->c && this->c == this->d)) {
        throw GeometryError("� �������� ��� ������� ������ ���� �����");
    }
    // ���� 90 ��� ���������� ������� ������� RectangleQ
}