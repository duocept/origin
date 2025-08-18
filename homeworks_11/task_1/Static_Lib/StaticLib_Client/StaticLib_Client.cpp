#include <iostream>
#include <string>
#include <windows.h>
#include "Greeter.h"

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    std::cout << "Введите имя: ";
    std::string name;
    std::getline(std::cin, name);

    greet::Greeter g;
    std::cout << g.greet(name) << std::endl;
    return 0;
}
