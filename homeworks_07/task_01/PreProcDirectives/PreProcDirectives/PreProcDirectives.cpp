#include <iostream>
#include <Windows.h>

#define MODE 1  // Здесь можно установить 0, 1 или другое значение

#ifndef MODE
#error "Вы должны определить константу MODE"
#endif

#if MODE == 1
int add(int a, int b) {
    return a + b;
}
#endif

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

#if MODE == 0
    std::cout << "Работаю в режиме тренировки" << std::endl;

#elif MODE == 1
    std::cout << "Работаю в боевом режиме" << std::endl;
    int x, y;
    std::cout << "Введите число 1: ";
    std::cin >> x;
    std::cout << "Введите число 2: ";
    std::cin >> y;
    std::cout << "Результат сложения: " << add(x, y) << std::endl;

#else
    std::cout << "Неизвестный режим. Завершение работы" << std::endl;
#endif

    return EXIT_SUCCESS;
}
