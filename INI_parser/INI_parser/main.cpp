#include <iostream>
#include "ini_parser.h"

#ifdef _WIN32
#include <windows.h>
#endif

enum class ReturnCode {
    Success = 0,
    ParseError = 1,
    KeyError = 2,
    UnknownError = 3
    
};


int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // вывод UTF-8
    SetConsoleCP(CP_UTF8);       // ввод UTF-8 (на будущее)
#endif
    try {
        ini::ini_parser parser("config.ini");

        // «section.key» вариант
        double v1 = parser.get_value<double>("Section1.var1");
        std::string s2 = parser.get_value<std::string>("Section2.var2");

        // секция + ключ вариант
        double d = parser.get_value<double>("Section1", "var1"); // если был переприсвоен — возьмёт последнее

        // пустое значение допустимо как строка
        std::string mode = parser.get_value<std::string>("Section4.Mode");

        // bool парсинг
        bool flag = parser.get_value<bool>("Flags.Enabled"); // для примера, если такое есть

        std::cout << v1 << " | " << s2 << " | " << d << " | \"" << mode << "\" | " << std::boolalpha << flag << "\n";

        return static_cast<int>(ReturnCode::Success);
    }
    catch (const ini::parse_error& e) {
        std::cerr << e.what() << "\n";
        return static_cast<int>(ReturnCode::ParseError);
    }
    catch (const ini::key_error& e) {
        std::cerr << e.what() << "\n";
        return static_cast<int>(ReturnCode::KeyError);
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        return static_cast<int>(ReturnCode::UnknownError);
    }
}
