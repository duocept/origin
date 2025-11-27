#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <random>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

HANDLE hConsole;
mutex consoleMutex;
int baseRow = 0;

const int INDEX_WIDTH = 3;
const int ID_WIDTH = 8;
const int BAR_WIDTH = 40;        // ширина прогресс-бара

WORD defaultAttr;   // исходные атрибуты
WORD filledAttr;    // «нормальный» прогресс (белый фон)
WORD errorAttr;     // прогресс на шаге с ошибкой (красный фон)

// index     – номер потока по порядку
// totalSteps – длина расчёта (кол-во шагов)
// stepMs    – задержка между шагами
void worker(int index, int totalSteps, int stepMs)
{
    DWORD id = GetCurrentThreadId();
    auto start = chrono::steady_clock::now();

    // состояние каждой ячейки прогресс-бара:
    // 0 – ещё не посчитана
    // 1 – посчитано успешно
    // 2 – на этом шаге была ошибка (exception)
    vector<int> cellState(BAR_WIDTH, 0);

    // генератор случайных чисел для имитации ошибок
    mt19937 rng(
        static_cast<unsigned>(
            chrono::steady_clock::now().time_since_epoch().count())
        + index * 12345);
    uniform_real_distribution<double> dist(0.0, 1.0);
    const double errorProb = 0.20; // 20% шанс «ошибки» на шаге

    // ВАЖНО: здесь totalSteps == BAR_WIDTH (см. main),
    // поэтому 1 шаг == 1 ячейка.
    for (int step = 0; step <= totalSteps; ++step)
    {
        if (step > 0) // начиная с шага 1 заполняем ячейки
        {
            int cellIndex = step - 1;      // какая ячейка сейчас считается
            bool isError = false;

            // --- имитируем расчёт с возможной ошибкой ---
            try
            {
                // "тяжёлый расчёт" мог бы быть здесь…
                // А мы просто иногда бросаем исключение.
                if (dist(rng) < errorProb)
                    throw runtime_error("Simulated error");
            }
            catch (const exception&)
            {
                // исключение не прерывает поток
                isError = true;
            }

            cellState[cellIndex] = isError ? 2 : 1;
        }

        auto now = chrono::steady_clock::now();
        double elapsed = chrono::duration<double>(now - start).count();

        {
            lock_guard<mutex> lock(consoleMutex);

            COORD pos;
            pos.X = 0;
            pos.Y = static_cast<SHORT>(baseRow + index);
            SetConsoleCursorPosition(hConsole, pos);

            cout << right;

            // # (номер потока)
            cout << setw(INDEX_WIDTH) << index << " ";
            // id
            cout << setw(ID_WIDTH) << id << "  ";

            // --- отрисовка прогресс-бара с учётом ошибок ---
            for (int i = 0; i < BAR_WIDTH; ++i)
            {
                if (cellState[i] == 0) {                // ещё не посчитано
                    SetConsoleTextAttribute(hConsole, defaultAttr);
                }
                else if (cellState[i] == 1) {         // успех
                    SetConsoleTextAttribute(hConsole, filledAttr);
                }
                else {                                // cellState[i] == 2, была ошибка
                    SetConsoleTextAttribute(hConsole, errorAttr);
                }
                cout << ' ';
            }

            // вернём стандартный цвет
            SetConsoleTextAttribute(hConsole, defaultAttr);
            cout << "  ";

            // время только после завершения всех шагов
            if (step == totalSteps) {
                cout << fixed << setprecision(5) << elapsed << "s";
            }
            else {
                cout << "          ";
            }

            cout.flush();
        }

        if (step < totalSteps)
            this_thread::sleep_for(chrono::milliseconds(stepMs));
    }
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // вывод UTF-8
    SetConsoleCP(CP_UTF8);       // ввод UTF-8 (на будущее)
#endif

    int numThreads = 5;           // количество потоков
    int totalSteps = BAR_WIDTH;   // длина расчёта = кол-во ячеек бара
    int stepMs = 150;         // задержка между шагами

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // исходные атрибуты
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    defaultAttr = csbi.wAttributes;

    // белый фон для «нормального» прогресса
    filledAttr = (defaultAttr & 0x0F) |
        BACKGROUND_RED | BACKGROUND_GREEN |
        BACKGROUND_BLUE | BACKGROUND_INTENSITY;

    // красный фон для шага с ошибкой
    errorAttr = (defaultAttr & 0x0F) |
        BACKGROUND_RED | BACKGROUND_INTENSITY;

    // шапка
    cout << setw(INDEX_WIDTH) << "#" << " "
        << setw(ID_WIDTH) << "id" << "  "
        << left << setw(BAR_WIDTH) << "Progress Bar"
        << right << "  Time\n";

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    baseRow = csbi.dwCursorPosition.Y;

    // строки под прогресс-бары
    for (int i = 0; i < numThreads; ++i)
        cout << '\n';

    // запуск потоков
    vector<thread> threads;
    threads.reserve(numThreads);
    for (int i = 0; i < numThreads; ++i)
        threads.emplace_back(worker, i, totalSteps, stepMs);

    for (auto& t : threads)
        t.join();

    // курсор под таблицу
    {
        lock_guard<mutex> lock(consoleMutex);
        COORD pos;
        pos.X = 0;
        pos.Y = static_cast<SHORT>(baseRow + numThreads + 1);
        SetConsoleCursorPosition(hConsole, pos);
    }

    cout << "\nГотово.\n";
    return 0;
}
