#pragma once

#include <string>

// Базовый класс-команда
class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

// Команда: вывод в консоль
class ConsoleLogCommand : public LogCommand {
public:
    void print(const std::string& message) override;
};

// Команда: вывод в файл
class FileLogCommand : public LogCommand {
public:
    explicit FileLogCommand(const std::string& filePath);

    void print(const std::string& message) override;

private:
    std::string filePath_;
};

// Свободная функция из задания 1, которая "выполняет команду"
void print(LogCommand& command, const std::string& message);

