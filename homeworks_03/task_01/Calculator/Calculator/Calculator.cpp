#include <iostream>
#include <Windows.h>

class Calculator {
private:
    double num1{};
    double num2{};

public:
    bool set_num1(double num1) {
        if (num1 != 0) {
            this->num1 = num1;
            return true;
        }
        return false;
    }

    bool set_num2(double num2) {
        if (num2 != 0) {
            this->num2 = num2;
            return true;
        }
        return false;
    }

    double add() const {
        return num1 + num2;
    }

    double multiply() const {
        return num1 * num2;
    }

    double subtract_1_2() const {
        return num1 - num2;
    }

    double subtract_2_1() const {
        return num2 - num1;
    }

    double divide_1_2() const {
        return num1 / num2;
    }

    double divide_2_1() const {
        return num2 / num1;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Calculator calc;
    double a, b;

    while (true) {
        std::cout << "Введите num1: ";
        std::cin >> a;
        std::cout << "Введите num2: ";
        std::cin >> b;

        if (calc.set_num1(a) && calc.set_num2(b)) {
            std::cout << "num1 + num2 = " << calc.add() << std::endl;
            std::cout << "num1 - num2 = " << calc.subtract_1_2() << std::endl;
            std::cout << "num2 - num1 = " << calc.subtract_2_1() << std::endl;
            std::cout << "num1 * num2 = " << calc.multiply() << std::endl;
            std::cout << "num1 / num2 = " << calc.divide_1_2() << std::endl;
            std::cout << "num2 / num1 = " << calc.divide_2_1() << std::endl;
        }
        else {
            std::cout << "Неверный ввод!" << std::endl;
        }

        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}