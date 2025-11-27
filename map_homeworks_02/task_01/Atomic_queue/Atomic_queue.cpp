#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// --- Настройка упорядочения памяти -----------------------
// Вариант 1: всё по умолчанию (самый строгий порядок)
// const memory_order COUNTER_ORDER     = memory_order_seq_cst;
// const memory_order FLAG_STORE_ORDER  = memory_order_seq_cst;
// const memory_order FLAG_LOAD_ORDER   = memory_order_seq_cst;

// Вариант 2: минимально необходимая синхронизация
//   - счётчик: relaxed (нет другой связанной общей памяти)
//   - флаг завершения: release / acquire
const memory_order COUNTER_ORDER = memory_order_relaxed;
const memory_order FLAG_STORE_ORDER = memory_order_release;
const memory_order FLAG_LOAD_ORDER = memory_order_acquire;

// ---------------------------------------------------------

// Атомарный счётчик клиентов
atomic<int> clientCounter{ 0 };
// Флаг: поток клиентов закончил работу и новых не будет
atomic<bool> noMoreClients{ false };

void clientThreadFunc(int maxClients)
{
    for (int i = 0; i < maxClients; ++i)
    {
        this_thread::sleep_for(chrono::seconds(1));

        // атомарное увеличение счётчика
        int newValue = clientCounter.fetch_add(1, COUNTER_ORDER) + 1;

        cout << "[Клиент] Пришёл новый клиент. В очереди теперь: "
            << newValue << endl;
    }

    // сообщаем, что новых клиентов не будет
    noMoreClients.store(true, FLAG_STORE_ORDER);
    cout << "[Клиент] Новых клиентов больше не будет." << endl;
}

void operatorThreadFunc()
{
    while (true)
    {
        this_thread::sleep_for(chrono::seconds(2));

        // читаем текущее значение счётчика
        int current = clientCounter.load(COUNTER_ORDER);

        if (current > 0)
        {
            // атомарно уменьшаем счётчик
            int newValue = clientCounter.fetch_sub(1, COUNTER_ORDER) - 1;

            cout << "[Оператор] Обслужил клиента. В очереди осталось: "
                << newValue << endl;
        }
        else
        {
            // клиентов в очереди нет — проверяем, будут ли ещё
            bool finished = noMoreClients.load(FLAG_LOAD_ORDER);

            if (finished)
            {
                cout << "[Оператор] Клиентов нет и больше не будет. "
                    << "Завершаю работу." << endl;
                break;
            }
            else
            {
                cout << "[Оператор] Очередь пустая, но клиенты ещё могут прийти."
                    << endl;
            }
        }
    }
}

int main()
{

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // вывод UTF-8
    SetConsoleCP(CP_UTF8);       // ввод UTF-8 (на будущее)
#endif

    int maxClients;

    cout << "Введите максимальное количество клиентов: ";
    cin >> maxClients;

    if (maxClients <= 0)
    {
        cout << "Максимальное количество клиентов должно быть > 0." << endl;
        return 0;
    }

    thread clientThread(clientThreadFunc, maxClients);
    thread operatorThread(operatorThreadFunc);

    clientThread.join();
    operatorThread.join();

    cout << "Работа завершена. Итоговый счётчик: "
        << clientCounter.load(COUNTER_ORDER) << endl;

    return 0;
}
