#include <iostream>
#include <vector>
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

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::vector<Figure*> figures = {
        new Triangle(10, 20, 30, 50, 60, 70),
        new RightTriangle(10, 20, 30, 50, 60),
        new IsoscelesTriangle(10, 20, 50, 60),
        new EquilateralTriangle(30),
        new Quadrangle(10, 20, 30, 40, 50, 60, 70, 80),
        new RectangleQ(10, 20),
        new Square(20),
        new Parallelogram(20, 30, 30, 40),
        new Rhombus(30, 30, 40)
    };

    for (Figure* fig : figures) {
        fig->print_info();
        delete fig;
    }

    return EXIT_SUCCESS;
}