#include <iostream>
#include <memory>

#include "LogCommand.h"   // ConsoleLogCommand, FileLogCommand, print(...)
#include "LogSubject.h"   // LogSubject
#include "Observers.h"    // WarningObserver, ErrorObserver, FatalErrorObserver
#include "LogMessage.h"   // LogMessage
#include "LogHandler.h"   // LogHandler и наследники: FatalErrorHandler, ErrorHandler, WarningHandler, UnknownMessageHandler

#ifdef _WIN32
#include <windows.h>
#endif

int main() {

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // вывод UTF-8
    SetConsoleCP(CP_UTF8);       // ввод UTF-8
#endif

    //==========================================================
    // 1. Паттерн «Команда» (задание 1)
    //==========================================================
    {
        std::cout << "=== Демонстрация паттерна \"Команда\" ===\n";

        ConsoleLogCommand consoleCmd;
        FileLogCommand fileCmd("command_log.txt");

        print(consoleCmd, "[Command] Сообщение через команду в консоль");
        print(fileCmd, "[Command] Сообщение через команду в файл");

        std::cout << std::endl;
    }

    //==========================================================
    // 2. Паттерн «Наблюдатель» + команды (задание 2)
    //==========================================================
    {
        std::cout << "=== Демонстрация паттерна \"Наблюдатель\" ===\n";

        LogSubject subject;

        // Наблюдатель для предупреждений — пишет в консоль (через ConsoleLogCommand)
        auto warnObserver = std::make_shared<WarningObserver>(
            std::make_unique<ConsoleLogCommand>());

        // Наблюдатель для ошибок — пишет в файл (через FileLogCommand)
        auto errorObserver = std::make_shared<ErrorObserver>(
            std::make_unique<FileLogCommand>("observer_errors.log"));

        // Наблюдатель для фатальных ошибок — и в консоль, и в файл
        auto fatalObserver = std::make_shared<FatalErrorObserver>(
            std::make_unique<ConsoleLogCommand>(),
            std::make_unique<FileLogCommand>("observer_fatal.log"));

        subject.addObserver(warnObserver);
        subject.addObserver(errorObserver);
        subject.addObserver(fatalObserver);

        subject.warning("Observer: мало свободного места на диске");
        subject.error("Observer: не удалось открыть конфигурационный файл");
        subject.fatalError("Observer: фатальная ошибка, приложение будет остановлено");

        std::cout << std::endl;
    }

    //==========================================================
    // 3. Паттерн «Цепочка ответственности» (задание 3)
    //==========================================================
    {
        std::cout << "=== Демонстрация паттерна \"Цепочка ответственности\" ===\n";

        // Строим цепочку:
        //
        // FatalErrorHandler -> ErrorHandler -> WarningHandler -> UnknownMessageHandler
        //
        UnknownMessageHandler unknownHandler;                     // последний в цепочке
        WarningHandler       warningHandler(&unknownHandler);     // предупреждения в консоль
        ErrorHandler         errorHandler("chain_errors.log",
            &warningHandler);       // ошибки в файл
        FatalErrorHandler    fatalHandler(&errorHandler);         // фатальные ошибки — исключение

        // 3.1. Сообщения Warning и Error (без падения программы)
        try {
            LogMessage warnMsg(LogMessage::Type::Warning,
                "Chain: мало памяти");
            fatalHandler.handle(warnMsg);   // обработает WarningHandler

            LogMessage errMsg(LogMessage::Type::Error,
                "Chain: база данных недоступна");
            fatalHandler.handle(errMsg);    // обработает ErrorHandler (запишет в файл)
        }
        catch (const std::exception& ex) {
            std::cerr << "[main] Исключение (warning/error): "
                << ex.what() << std::endl;
        }

        // 3.2. Неизвестное сообщение — дойдёт до UnknownMessageHandler и выбросит исключение
        try {
            LogMessage unknownMsg(LogMessage::Type::Unknown,
                "Chain: непонятное состояние системы");
            fatalHandler.handle(unknownMsg);
        }
        catch (const std::exception& ex) {
            std::cerr << "[main] Исключение (unknown): "
                << ex.what() << std::endl;
        }

        // 3.3. Фатальная ошибка — FatalErrorHandler сразу бросит исключение
        try {
            LogMessage fatalMsg(LogMessage::Type::FatalError,
                "Chain: критический сбой, завершение работы");
            fatalHandler.handle(fatalMsg);
        }
        catch (const std::exception& ex) {
            std::cerr << "[main] Исключение (fatal): "
                << ex.what() << std::endl;
        }

        std::cout << std::endl;
    }

    std::cout << "=== Конец демонстрации всех трёх паттернов ===\n";
    return 0;
}
