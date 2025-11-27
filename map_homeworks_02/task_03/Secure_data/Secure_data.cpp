#include <iostream>
#include <mutex>
#include <thread>
#include <utility>

#ifdef _WIN32
#include <windows.h>
#endif

class Data {
public:
    int value;          // какие-то скалярные данные
    mutable std::mutex m; // мьютекс (mutable, чтобы можно было блокировать в const-функциях при желании)

    explicit Data(int v = 0) : value(v) {}
};

/// Вариант 1: std::lock + lock_guard(adopt_lock)
void swap_lock(Data& a, Data& b)
{
    if (&a == &b) return; // защита от самосвапа

    // 1) атомарно блокируем оба мьютекса (без риска дедлока)
    std::lock(a.m, b.m);

    // 2) "забираем" владение уже заблокированными мьютексами
    std::lock_guard<std::mutex> lockA(a.m, std::adopt_lock);
    std::lock_guard<std::mutex> lockB(b.m, std::adopt_lock);

    // 3) безопасно меняем данные
    std::swap(a.value, b.value);
}

/// Вариант 2: std::scoped_lock (C++17)
void swap_scoped_lock(Data& a, Data& b)
{
    if (&a == &b) return;

    // scoped_lock сам блокирует несколько мьютексов без дедлока
    std::scoped_lock guard(a.m, b.m);
    std::swap(a.value, b.value);
}

/// Вариант 3: std::unique_lock + std::lock
void swap_unique_lock(Data& a, Data& b)
{
    if (&a == &b) return;

    // создаём unique_lock без захвата мьютексов
    std::unique_lock<std::mutex> lockA(a.m, std::defer_lock);
    std::unique_lock<std::mutex> lockB(b.m, std::defer_lock);

    // std::lock блокирует оба unique_lock, избегая дедлока
    std::lock(lockA, lockB);

    std::swap(a.value, b.value);
}

// Небольшая проверка
int main()
{

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // вывод UTF-8
    SetConsoleCP(CP_UTF8);       // ввод UTF-8 (на будущее)
#endif

    Data d1(10);
    Data d2(20);

    std::cout << "До swap_lock:      d1=" << d1.value << " d2=" << d2.value << '\n';
    swap_lock(d1, d2);
    std::cout << "После swap_lock:   d1=" << d1.value << " d2=" << d2.value << '\n';

    swap_scoped_lock(d1, d2);
    std::cout << "После swap_scoped: d1=" << d1.value << " d2=" << d2.value << '\n';

    swap_unique_lock(d1, d2);
    std::cout << "После swap_unique: d1=" << d1.value << " d2=" << d2.value << '\n';

    return 0;
}
