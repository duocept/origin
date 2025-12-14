#include "LogCommand.h"

#include <iostream>
#include <fstream>

void ConsoleLogCommand::print(const std::string& message) {
    std::cout << message << std::endl;
}

FileLogCommand::FileLogCommand(const std::string& filePath)
    : filePath_(filePath) {
}

void FileLogCommand::print(const std::string& message) {
    std::ofstream out(filePath_, std::ios::app);
    if (!out) {
        std::cerr << "Не удалось открыть файл лога: " << filePath_ << std::endl;
        return;
    }
    out << message << std::endl;
}

void print(LogCommand& command, const std::string& message) {
    command.print(message);
}
