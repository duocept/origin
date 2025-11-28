#include <algorithm>
#include <future>
#include <iterator>
#include <vector>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

// Параллельный for_each: рекурсивно делим диапазон и обрабатываем в нескольких задачах
template <typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func& func)
{
    using diff_t = typename std::iterator_traits<Iterator>::difference_type;

    diff_t length = std::distance(first, last);
    if (length <= 0) return;

    // Минимальный размер блока, при котором ещё имеет смысл создавать задачу
    const diff_t min_per_task = 1000;

    if (length <= min_per_task)
    {
        // Маленький блок — просто обычный std::for_each в текущем потоке
        std::for_each(first, last, func);
    }
    else
    {
        // Делим диапазон пополам
        Iterator mid = first;
        std::advance(mid, length / 2);

        // Запускаем задачу для правой половины
        auto future = std::async(std::launch::async,
            [mid, last, &func]() {
                parallel_for_each(mid, last, func);
            });

        // Левую половину обрабатываем в текущем потоке
        parallel_for_each(first, mid, func);

        // Ждём завершения задачи
        future.get();
    }
}

// Пример использования
int main()
{

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // вывод UTF-8
    SetConsoleCP(CP_UTF8);       // ввод UTF-8 (на будущее)
#endif

    std::vector<int> data;
    for (int i = 0; i < 10000; ++i)
        data.push_back(i);

    auto op = [](int& x) {
        x *= 2;  // любая обработка элемента
        };

    parallel_for_each(data.begin(), data.end(), op);

    // Проверка (выведем первые пару значений)
    std::cout << data[0] << " " << data[1] << " " << data[2] << " " << data[3] << " " << data[4] << "\n";
}
