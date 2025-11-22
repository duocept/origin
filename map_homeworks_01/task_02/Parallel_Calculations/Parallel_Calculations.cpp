#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Рабочая функция: суммирует от [begin, end)
void sumSegment(const vector<double>& a,
    const vector<double>& b,
    vector<double>& c,
    size_t begin,
    size_t end)
{
    for (size_t i = begin; i < end; ++i) {
        c[i] = a[i] + b[i];
    }
}

// Функция, считающая сумму в numThreads потоков и возвращающая время в секундах
double measureSumTime(size_t size, int numThreads)
{
    // Инициализация векторов
    vector<double> a(size), b(size), c(size);
    for (size_t i = 0; i < size; ++i) {
        a[i] = static_cast<double>(i);
        b[i] = static_cast<double>(size - i);
    }

    auto start = chrono::high_resolution_clock::now();

    vector<thread> threads;
    threads.reserve(numThreads);

    // Разбиваем работу по потокам
    size_t baseChunk = size / numThreads;
    size_t remainder = size % numThreads;

    size_t begin = 0;
    for (int t = 0; t < numThreads; ++t) {
        size_t chunk = baseChunk + (t < static_cast<int>(remainder) ? 1 : 0);
        size_t end = begin + chunk;

        threads.emplace_back(sumSegment, cref(a), cref(b), ref(c), begin, end);

        begin = end;
    }

    for (auto& th : threads) {
        th.join();
    }

    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = finish - start;
    return diff.count();
}

// Первый запущенный поток — выводит количество аппаратных ядер
void printHardwareThreads()
{
    unsigned int n = thread::hardware_concurrency();
    if (n == 0)
        cout << "Количество аппаратных ядер определить не удалось" << endl;
    else
        cout << "Количество аппаратных ядер - " << n << endl;
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // вывод UTF-8
    SetConsoleCP(CP_UTF8);       // ввод UTF-8 (на будущее)
#endif

    // Первый поток — просто вывод информации о ядрах
    thread infoThread(printHardwareThreads);
    infoThread.join();
    cout << endl;

    vector<size_t> sizes = { 1000, 10000, 100000, 1000000 };
    vector<int> threadCounts = { 1, 2, 4, 8, 16 };

    cout << fixed << setprecision(6);

    // Заголовок таблицы
    cout << setw(12) << "";
    for (size_t size : sizes) {
        cout << setw(12) << size;
    }
    cout << endl;

    // Строки: 1, 2, 4, 8, 16 потоков
    for (int threads : threadCounts) {
        cout << setw(3) << threads << " потоков";

        for (size_t size : sizes) {
            double t = measureSumTime(size, threads);
            cout << setw(10) << t << "s";
        }
        cout << endl;
    }

    return 0;
}
