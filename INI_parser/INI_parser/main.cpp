#include <iostream>
#include "ini_parser.h"

int main() {
    try {
        ini::ini_parser parser("config.ini");

        // «section.key» вариант
        int v1 = parser.get_value<double>("Section1.var1");
        std::string s2 = parser.get_value<std::string>("Section2.var2");

        // секция + ключ вариант
        double d = parser.get_value<double>("Section1", "var1"); // если был переприсвоен — возьмёт последнее

        // пустое значение допустимо как строка
        std::string mode = parser.get_value<std::string>("Section4.Mode");

        // bool парсинг
        bool flag = parser.get_value<bool>("Flags.Enabled"); // для примера, если такое есть

        std::cout << v1 << " | " << s2 << " | " << d << " | \"" << mode << "\" | " << std::boolalpha << flag << "\n";
    }
    catch (const ini::parse_error& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    catch (const ini::key_error& e) {
        std::cerr << e.what() << "\n";
        return 2;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        return 3;
    }
}
