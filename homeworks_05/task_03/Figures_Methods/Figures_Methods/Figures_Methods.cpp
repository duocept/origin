#include <iostream>
#include <string>
#include <Windows.h>


class Figure {
protected:
    std::string name;
    int sides_count = 0;

public:
    Figure(const std::string& name, int sides) : name(name), sides_count(sides) {}
    virtual bool check() const { return sides_count == 0; }

    virtual void print_info() const {
        std::cout << name << ":\n";
        std::cout << (check() ? "Правильная" : "Неправильная") << std::endl;
        std::cout << "Количество сторон: " << sides_count << std::endl << std::endl;
    }

    virtual ~Figure() = default;
};

class Triangle : public Figure {
protected:
    int a, b, c;      // Стороны
    int A, B, C;      // Углы

public:
    Triangle(int a, int b, int c, int A, int B, int C)
        : Figure("Треугольник", 3), a(a), b(b), c(c), A(A), B(B), C(C) {}

    bool check() const override {
        return A + B + C == 180;
    }

    void print_info() const override {
        Figure::print_info();
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

    bool check() const override {
        return Triangle::check() && C == 90;
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(int a, int b, int A, int B)
        : Triangle(a, b, a, A, B, A) {
        name = "Равнобедренный треугольник";
    }

    bool check() const override {
        return Triangle::check() && a == c && A == C;
    }
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(int a)
        : Triangle(a, a, a, 60, 60, 60) {
        name = "Равносторонний треугольник";
    }

    bool check() const override {
        return Triangle::check() && a == b && b == c && A == B && B == C && A == 60;
    }
};

class Quadrangle : public Figure {
protected:
    int a, b, c, d;
    int A, B, C, D;

public:
    Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D)
        : Figure("Четырёхугольник", 4), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {}

    bool check() const override {
        return A + B + C + D == 360;
    }

    void print_info() const override {
        Figure::print_info();
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

    bool check() const override {
        return Quadrangle::check() && a == c && b == d && A == B && B == C && C == D && A == 90;
    }
};

class Square : public RectangleQ {
public:
    Square(int a)
        : RectangleQ(a, a) {
        name = "Квадрат";
    }

    bool check() const override {
        return RectangleQ::check() && a == b && a == c && a == d;
    }
};

class Parallelogram : public Quadrangle {
public:
    Parallelogram(int a, int b, int A, int B)
        : Quadrangle(a, b, a, b, A, B, A, B) {
        name = "Параллелограмм";
    }

    bool check() const override {
        return Quadrangle::check() && a == c && b == d && A == C && B == D;
    }
};

class Rhombus : public Parallelogram {
public:
    Rhombus(int a, int A, int B)
        : Parallelogram(a, a, A, B) {
        name = "Ромб";
    }

    bool check() const override {
        return Parallelogram::check() && a == b && b == c && c == d;
    }
};

void print_info(const Figure* figure) {
    figure->print_info();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Figure* figures[] = {
        new Figure("Фигура", 0),
        new Triangle(10, 20, 30, 50, 60, 70),
        new RightTriangle(10, 20, 30, 50, 60),
        new RightTriangle(10, 20, 30, 50, 40),
        new IsoscelesTriangle(10, 20, 50, 60),
        new EquilateralTriangle(30),
        new Quadrangle(10, 20, 30, 40, 50, 60, 70, 80),
        new RectangleQ(10, 20),
        new Square(20),
        new Parallelogram(20, 30, 30, 40),
        new Rhombus(30, 30, 40)
    };

    for (Figure* fig : figures) {
        print_info(fig);
        delete fig;
    }

    return EXIT_SUCCESS;
}