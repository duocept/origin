#include <iostream>
#include <string>
#include <windows.h>


int main() {

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    std::cout << "Введите имя: ";
    std::string name;
    std::getline(std::cin, name);

    std::cout << "Здравствуйте, " << name << "!" << std::endl;
    return 0;
}