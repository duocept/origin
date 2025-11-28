#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <iterator>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

// Асинхронный поиск минимального элемента на участке [first, last)
template <typename RandomIt>
RandomIt async_find_min(RandomIt first, RandomIt last)
{
    using It = RandomIt;

    // Обещание вернуть итератор на минимальный элемент
    std::promise<It> prom;
    std::future<It> fut = prom.get_future();

    // Запускаем отдельный поток
    std::thread worker(
        [first, last, p = std::move(prom)]() mutable
        {
            // Предполагаем, что диапазон не пустой
            It minIt = first;
            It it = first;
            ++it; // начинаем сравнение со второго элемента

            for (; it != last; ++it)
            {
                if (*it < *minIt)
                    minIt = it;
            }

            // Возвращаем найденный итератор через promise
            p.set_value(minIt);
        }
    );

    // Поток нам больше не нужен напрямую
    worker.detach();

    // Ждём результат (блокируемся, пока поток не выполнит set_value)
    return fut.get();
}

// Сортировка выбором с использованием async_find_min
template <typename RandomIt>
void selection_sort(RandomIt first, RandomIt last)
{
    for (auto it = first; it != last; ++it)
    {
        // Асинхронно ищем минимум на хвосте [it, last)
        RandomIt minIt = async_find_min(it, last);

        // Меняем местами текущий элемент и найденный минимум
        if (minIt != it)
            std::iter_swap(it, minIt);
    }
}

int main()
{

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // вывод UTF-8
    SetConsoleCP(CP_UTF8);       // ввод UTF-8 (на будущее)
#endif

    std::vector<int> data{ 64, 25, 12, 22, 11 };

    std::cout << "До сортировки: ";
    for (int x : data) std::cout << x << ' ';
    std::cout << '\n';

    selection_sort(data.begin(), data.end());

    std::cout << "После сортировки: ";
    for (int x : data) std::cout << x << ' ';
    std::cout << '\n';

    return 0;
}
