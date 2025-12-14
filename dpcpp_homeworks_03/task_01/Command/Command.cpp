#include <iostream>
#include <fstream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

// Базовый класс-команда
class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

// Команда: вывод в консоль
class ConsoleLogCommand : public LogCommand {
public:
    void print(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

// Команда: вывод в файл
class FileLogCommand : public LogCommand {
public:
    explicit FileLogCommand(const std::string& filePath)
        : m_filePath(filePath) {
    }

    void print(const std::string& message) override {
        std::ofstream out(m_filePath, std::ios::app); // дозапись в конец файла
        if (!out) {
            std::cerr << "Не удалось открыть файл лога: " << m_filePath << std::endl;
            return;
        }
        out << message << std::endl;
    }

private:
    std::string m_filePath;
};

// Функция, которая «выполняет команду»
void print(LogCommand& command, const std::string& message) {
    command.print(message);
}

int main() {

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // вывод UTF-8
    SetConsoleCP(CP_UTF8);       // ввод UTF-8 (на будущее)
#endif

    // Создаём команды
    ConsoleLogCommand consoleLogger;
    FileLogCommand fileLogger("log.txt");

    // Выполняем команды через общую функцию
    print(consoleLogger, "Сообщение в консоль");
    print(fileLogger, "Сообщение в файл");

    return 0;
}
