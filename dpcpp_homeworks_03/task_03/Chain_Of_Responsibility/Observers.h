#pragma once
#include <memory>
#include <string>

#include "Observer.h"
#include "LogCommand.h"

// 1) Наблюдатель для предупреждений — пишет в консоль (через команду)
class WarningObserver : public Observer {
public:
    explicit WarningObserver(std::unique_ptr<LogCommand> command);

    void onWarning(const std::string& message) override;

private:
    std::unique_ptr<LogCommand> command_;
};

// 2) Наблюдатель для ошибок — пишет в файл (через команду)
class ErrorObserver : public Observer {
public:
    explicit ErrorObserver(std::unique_ptr<LogCommand> command);

    void onError(const std::string& message) override;

private:
    std::unique_ptr<LogCommand> command_;
};

// 3) Наблюдатель для фатальных ошибок — и в консоль, и в файл
class FatalErrorObserver : public Observer {
public:
    FatalErrorObserver(std::unique_ptr<LogCommand> consoleCommand,
        std::unique_ptr<LogCommand> fileCommand);

    void onFatalError(const std::string& message) override;

private:
    std::unique_ptr<LogCommand> consoleCommand_;
    std::unique_ptr<LogCommand> fileCommand_;
};
