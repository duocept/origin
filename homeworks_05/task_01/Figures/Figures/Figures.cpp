#include <iostream>
#include <string>
#include <Windows.h>

// Базовый класс
class Figure {
protected:
    int sides_count;
    std::string name;

    // Защищённый конструктор с параметрами для инициализации
    Figure(int sides, const std::string& name)
        : sides_count(sides), name(name) {}

public:
    // Публичный конструктор по умолчанию для неизвестной фигуры
    Figure() : Figure(0, "Фигура") {}

    int get_sides_count() const {
        return sides_count;
    }

    std::string get_name() const {
        return name;
    }
};

// Производный класс — Треугольник
class Triangle : public Figure {
public:
    Triangle() : Figure(3, "Треугольник") {}
};

// Производный класс — Четырёхугольник
class Quadrangle : public Figure {
public:
    Quadrangle() : Figure(4, "Четырёхугольник") {}
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Figure figure;
    Triangle triangle;
    Quadrangle quadrangle;

    std::cout << "Количество сторон:" << std::endl;
    std::cout << figure.get_name() << ": " << figure.get_sides_count() << std::endl;
    std::cout << triangle.get_name() << ": " << triangle.get_sides_count() << std::endl;
    std::cout << quadrangle.get_name() << ": " << quadrangle.get_sides_count() << std::endl;

    return EXIT_SUCCESS;
}