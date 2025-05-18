#include <iostream>
#include <string>
#include <Windows.h>

class Figure {
protected:
    std::string name;

public:
    Figure(const std::string& name) : name(name) {}
    virtual void print_info() const = 0;
    virtual ~Figure() = default;
};

class Triangle : public Figure {
protected:
    int a, b, c;      // Стороны
    int A, B, C;      // Углы

public:
    Triangle(int a, int b, int c, int A, int B, int C)
        : Figure("Треугольник"), a(a), b(b), c(c), A(A), B(B), C(C) {}

    void print_info() const override {
        std::cout << name << ":\n";
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << std::endl;
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << std::endl << std::endl;
    }
};

class RightTriangle : public Triangle {
public:
    RightTriangle(int a, int b, int c, int A, int B)
        : Triangle(a, b, c, A, B, 90) {
        name = "Прямоугольный треугольник";
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(int a, int b, int A, int B)
        : Triangle(a, b, a, A, B, A) {
        name = "Равнобедренный треугольник";
    }
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(int a)
        : Triangle(a, a, a, 60, 60, 60) {
        name = "Равносторонний треугольник";
    }
};

class Quadrangle : public Figure {
protected:
    int a, b, c, d;
    int A, B, C, D;

public:
    Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D)
        : Figure("Четырёхугольник"), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {}

    void print_info() const override {
        std::cout << name << ":\n";
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << std::endl;
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << std::endl << std::endl;
    }
};

class RectangleQ : public Quadrangle {
public:
    RectangleQ(int a, int b)
        : Quadrangle(a, b, a, b, 90, 90, 90, 90) {
        name = "Прямоугольник";
    }
};

class Square : public RectangleQ {
public:
    Square(int a)
        : RectangleQ(a, a) {
        name = "Квадрат";
    }
};

class Parallelogram : public Quadrangle {
public:
    Parallelogram(int a, int b, int A, int B)
        : Quadrangle(a, b, a, b, A, B, A, B) {
        name = "Параллелограмм";
    }
};

class Rhombus : public Parallelogram {
public:
    Rhombus(int a, int A, int B)
        : Parallelogram(a, a, A, B) {
        name = "Ромб";
    }
};

void print_info(const Figure* figure) {
    figure->print_info();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Triangle t(10, 20, 30, 50, 60, 70);
    RightTriangle rt(10, 20, 30, 50, 60);
    IsoscelesTriangle it(10, 20, 50, 60);
    EquilateralTriangle et(30);

    Quadrangle q(10, 20, 30, 40, 50, 60, 70, 80);
    RectangleQ r(10, 20);
    Square s(20);
    Parallelogram p(20, 30, 30, 40);
    Rhombus rh(30, 30, 40);

    print_info(&t);
    print_info(&rt);
    print_info(&it);
    print_info(&et);
    print_info(&q);
    print_info(&r);
    print_info(&s);
    print_info(&p);
    print_info(&rh);

    return EXIT_SUCCESS;
}