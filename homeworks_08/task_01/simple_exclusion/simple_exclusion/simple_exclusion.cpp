#include <iostream>
#include <string>
#include <exception>
#include <windows.h>

class bad_length : public std::exception {
public:
    const char* what() const noexcept override {
        return "forbidden length";
    }
};

int function(const std::string& str, int forbidden_length) {
    int len = static_cast<int>(str.length());
    if (len == forbidden_length) {
        throw bad_length{};
    }
    return len;
}

int main() {

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    std::cout << "Введите запретную длину: ";
    int forbidden = 0;
    if (!(std::cin >> forbidden)) return 0;

    for (;;) {
        std::cout << "Введите слово: ";
        std::string word;
        if (!(std::cin >> word)) break;

        try {
            int len = function(word, forbidden);
            std::cout << "Длина слова \"" << word << "\" равна " << len << '\n';
        }
        catch (const bad_length&) {
            std::cout << "Вы ввели слово запретной длины! До свидания\n";
            break;
        }
    }
    return 0;
}
