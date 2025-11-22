#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Общая очередь клиентов
atomic<int> queueSize{ 0 };
// Флаг: true, когда клиентский поток закончил добавлять клиентов
atomic<bool> noMoreNewClients{ false };

void clientThreadFunc(int maxClients)
{
    for (int i = 0; i < maxClients; ++i)
    {
        this_thread::sleep_for(chrono::seconds(1)); // раз в секунду
        int newValue = ++queueSize; // атомарное увеличение
        cout << "[Клиент] Пришёл новый клиент. В очереди теперь: "
            << newValue << endl;
    }

    // Новых клиентов больше не будет
    noMoreNewClients = true;
    cout << "[Клиент] Больше клиентов не будет. Всего пришло: "
        << maxClients << endl;
}

void operatorThreadFunc()
{
    while (true)
    {
        this_thread::sleep_for(chrono::seconds(2)); // раз в 2 секунды

        // Если в очереди есть клиенты — обслуживаем
        int currentQueue = queueSize.load();
        if (currentQueue > 0)
        {
            int newValue = --queueSize; // атомарное уменьшение
            cout << "[Оператор] Обслужил клиента. В очереди осталось: "
                << newValue << endl;
        }
        else
        {
            // Клиентов нет. Проверяем, будут ли ещё.
            if (noMoreNewClients.load())
            {
                cout << "[Оператор] Клиентов нет и больше не будет. "
                    << "Завершаю работу." << endl;
                break;
            }
            else
            {
                cout << "[Оператор] Пока никого нет в очереди, жду..." << endl;
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

    // Стартуем два потока
    thread clientThread(clientThreadFunc, maxClients);
    thread operatorThread(operatorThreadFunc);

    // Ждём их завершения
    clientThread.join();
    operatorThread.join();

    cout << "Работа программы завершена. Итоговая длина очереди: "
        << queueSize.load() << endl;

    return 0;
}
