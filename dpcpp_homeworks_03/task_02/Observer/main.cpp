#include <memory>

#include "LogCommand.h"
#include "LogSubject.h"
#include "Observers.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // вывод UTF-8
    SetConsoleCP(CP_UTF8);       // ввод UTF-8 (на будущее)
#endif

    //Задание 1: паттерн "Команда"
    ConsoleLogCommand consoleCmd;
    FileLogCommand fileCmd("command_log.txt");

    print(consoleCmd, "Сообщение через команду в консоль");
    print(fileCmd, "Сообщение через команду в файл");

    //Задание 2: паттерн "Наблюдатель" + команды внутри наблюдателей
    LogSubject subject;

    // Наблюдатель для предупреждений — консоль
    auto warnObserver = std::make_shared<WarningObserver>(
        std::make_unique<ConsoleLogCommand>());

    // Наблюдатель для ошибок — файл
    auto errorObserver = std::make_shared<ErrorObserver>(
        std::make_unique<FileLogCommand>("errors.log"));

    // Наблюдатель для фатальных ошибок — и консоль, и файл
    auto fatalObserver = std::make_shared<FatalErrorObserver>(
        std::make_unique<ConsoleLogCommand>(),
        std::make_unique<FileLogCommand>("fatal.log"));

    // Подписываем наблюдателей
    subject.addObserver(warnObserver);
    subject.addObserver(errorObserver);
    subject.addObserver(fatalObserver);

    // Генерируем события
    subject.warning("Мало свободного места на диске");
    subject.error("Не удалось открыть конфигурационный файл");
    subject.fatalError("Критическая ошибка: закончилась память");

    return 0;
}
