#include <iostream>
#include <Windows.h>
#include "Figure.h"
#include "Triangle.h"
#include "RightTriangle.h"
#include "IsoscelesTriangle.h"
#include "EquilateralTriangle.h"
#include "Quadrangle.h"
#include "RectangleQ.h"
#include "Square.h"
#include "Parallelogram.h"
#include "Rhombus.h"
#include "GeometryError.h"

template <class Maker>
void try_make(Maker m) {
    try {
        Figure* f = m();
        f->print_info();
        delete f;
    } catch (const GeometryError& e) {
        std::cout << "������ �������� ������. �������: " << e.what() << std::endl;
    }
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try_make([]{ return new Triangle(10, 20, 30, 50, 60, 70); });        // ������: 50+60+70 != 180
    try_make([]{ return new RightTriangle(10, 20, 30, 50, 60); });       // ������: A+B+90 != 180
    try_make([]{ return new IsoscelesTriangle(10, 20, 50, 60); });       // ������: 50+60+50 != 180
    try_make([]{ return new EquilateralTriangle(30); });                 // ��
    try_make([]{ return new Quadrangle(10,20,30,40,50,60,70,80); });     // ������: 50+60+70+80 != 360
    try_make([]{ return new RectangleQ(10, 20); });                      // ��
    try_make([]{ return new Square(20); });                              // ��
    try_make([]{ return new Parallelogram(20, 30, 30, 40); });           // ������: ����� ����� 140
    try_make([]{ return new Rhombus(30, 120, 60); });                    // ��

    return 0;
}