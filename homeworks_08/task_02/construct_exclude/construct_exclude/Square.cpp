#include "Square.h"
#include "GeometryError.h"

Square::Square(int a)
    : RectangleQ(a, a)
{
    name = " вадрат";
    // ¬ RectangleQ уже обеспечены a=c и b=d; здесь проверим равенство всех сторон
    if (!(this->a == this->b && this->b == this->c && this->c == this->d)) {
        throw GeometryError("в квадрате все стороны должны быть равны");
    }
    // ”глы 90 уже обеспечены базовым классом RectangleQ
}