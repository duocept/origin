#include <iostream>
#include <Windows.h>
#include "math_functions.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    double a, b;
    int choice;

    std::cout << "Введите первое число: ";
    std::cin >> a;
    std::cout << "Введите второе число: ";
    std::cin >> b;

    std::cout << "Выберите операцию (1 - сложение, 2 - вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень): ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        std::cout << a << " + " << b << " = " << add(a, b) << std::endl;
        break;
    case 2:
        std::cout << a << " - " << b << " = " << subtract(a, b) << std::endl;
        break;
    case 3:
        std::cout << a << " * " << b << " = " << multiply(a, b) << std::endl;
        break;
    case 4:
        if (b != 0)
            std::cout << a << " / " << b << " = " << divide(a, b) << std::endl;
        else
            std::cout << "Ошибка: деление на ноль!" << std::endl;
        break;
    case 5:
        std::cout << a << " в степени " << b << " = " << power(a, b) << std::endl;
        break;
    default:
        std::cout << "Неизвестная операция" << std::endl;
    }

    return EXIT_SUCCESS;
}