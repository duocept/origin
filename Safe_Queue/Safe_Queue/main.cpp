#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include "thread_pool.h"

#ifdef _WIN32
#include <windows.h>
#endif

// Тестовые функции
void test_function_A(int id) {
    std::cout << "[A] Задача " << id
        << " старт, поток " << std::this_thread::get_id()
        << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(400));

    std::cout << "[A] Задача " << id
        << " финиш, поток " << std::this_thread::get_id()
        << std::endl;
}

void test_function_B(int id) {
    std::cout << "    [B] Задача " << id
        << " старт, поток " << std::this_thread::get_id()
        << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(700));

    std::cout << "    [B] Задача " << id
        << " финиш, поток " << std::this_thread::get_id()
        << std::endl;
}

int main() {

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // вывод UTF-8
    SetConsoleCP(CP_UTF8);       // ввод UTF-8
#endif

    thread_pool pool;

    std::vector<std::future<void>> futures;

    // Раз в секунду отправляем в пул две задачи
    const int iterations = 5; // для примера: 5 "секунд", по 2 задачи в каждую

    for (int i = 0; i < iterations; ++i) {
        std::cout << "\n=== Итерация " << i << " ===" << std::endl;

        // Одновременно кладём две разные функции
        futures.push_back(pool.submit(test_function_A, i));
        futures.push_back(pool.submit(test_function_B, i));

        // Ждём 1 секунду до следующей "подачи" задач
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Дождёмся завершения всех задач
    for (auto& f : futures) {
        f.get();
    }

    std::cout << "\nВсе задачи выполнены, выходим из main\n";

    return 0;
}
