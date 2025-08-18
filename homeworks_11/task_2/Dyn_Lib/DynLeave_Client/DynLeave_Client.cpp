#include <iostream>
#include <string>
#include <windows.h>
#include "Leaver.h"

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    std::cout << "Введите имя: ";
    std::string name;
    std::getline(std::cin, name);

    leave::Leaver g;
    std::cout << g.leave(name) << std::endl;
    return 0;
}