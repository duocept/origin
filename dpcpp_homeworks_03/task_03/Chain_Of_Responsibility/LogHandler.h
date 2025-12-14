#pragma once
#include <string>
#include "LogMessage.h"

class LogHandler {
public:
    explicit LogHandler(LogHandler* next = nullptr);
    virtual ~LogHandler() = default;

    void setNext(LogHandler* next);

    // основной интерфейс: обработать сообщение или передать дальше
    virtual void handle(const LogMessage& msg);

protected:
    LogHandler* next_;
};

// Обработчик фатальных ошибок
class FatalErrorHandler : public LogHandler {
public:
    using LogHandler::LogHandler; // конструктор базового класса

    void handle(const LogMessage& msg) override;
};

// Обработчик обычных ошибок — пишет в файл
class ErrorHandler : public LogHandler {
public:
    ErrorHandler(const std::string& filePath, LogHandler* next = nullptr);

    void handle(const LogMessage& msg) override;

private:
    std::string filePath_;
};

// Обработчик предупреждений — пишет в консоль
class WarningHandler : public LogHandler {
public:
    explicit WarningHandler(LogHandler* next = nullptr);

    void handle(const LogMessage& msg) override;
};

// Обработчик неизвестных сообщений — бросает исключение
class UnknownMessageHandler : public LogHandler {
public:
    using LogHandler::LogHandler;

    void handle(const LogMessage& msg) override;
};
