#include <iostream>
#include <string>
#include <Windows.h>
#include "counter.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Counter counter;
    std::string input;
    int initial_value = 1;

    std::cout << "Вы хотите указать начальное значение счётчика? Введите да или нет: ";
    std::cin >> input;

    if (input == "да" || input == "Да" || input == "ДА") {
        std::cout << "Введите начальное значение счётчика: ";
        std::cin >> initial_value;
        counter = Counter(initial_value);
    }

    while (true) {
        std::cout << "Введите команду ('+', '-', '=' или 'x'): ";
        std::cin >> input;

        if (input == "+") {
            counter.increment();
        }
        else if (input == "-") {
            counter.decrement();
        }
        else if (input == "=") {
            std::cout << counter.get_value() << std::endl;
        }
        else if (input == "x" || input == "х") {
            std::cout << "До свидания!" << std::endl;
            break;
        }
        else {
            std::cout << "Неизвестная команда!" << std::endl;
        }
    }

    return EXIT_SUCCESS;
}