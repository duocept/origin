#include "LogHandler.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

//Base

LogHandler::LogHandler(LogHandler* next)
    : next_(next) {
}

void LogHandler::setNext(LogHandler* next) {
    next_ = next;
}

void LogHandler::handle(const LogMessage& msg) {
    if (next_) {
        next_->handle(msg);
    }
}

//FatalErrorHandler

void FatalErrorHandler::handle(const LogMessage& msg) {
    if (msg.type() == LogMessage::Type::FatalError) {
        // фатальная ошибка — сразу кидаем исключение с текстом сообщения
        throw std::runtime_error(msg.message());
    }

    // если это не фатальная ошибка — передаём дальше по цепочке
    LogHandler::handle(msg);
}

//ErrorHandler

ErrorHandler::ErrorHandler(const std::string& filePath, LogHandler* next)
    : LogHandler(next)
    , filePath_(filePath) {
}

void ErrorHandler::handle(const LogMessage& msg) {
    if (msg.type() == LogMessage::Type::Error) {
        std::ofstream out(filePath_, std::ios::app);
        if (!out) {
            std::cerr << "[ErrorHandler] Не удалось открыть файл: "
                << filePath_ << std::endl;
            return;
        }
        out << "[Error] " << msg.message() << std::endl;
        return; // обработали, цепочку можно не продолжать
    }

    LogHandler::handle(msg);
}

//WarningHandler

WarningHandler::WarningHandler(LogHandler* next)
    : LogHandler(next) {
}

void WarningHandler::handle(const LogMessage& msg) {
    if (msg.type() == LogMessage::Type::Warning) {
        std::cout << "[Warning] " << msg.message() << std::endl;
        return;
    }

    LogHandler::handle(msg);
}

//UnknownMessageHandler

void UnknownMessageHandler::handle(const LogMessage& msg) {
    if (msg.type() == LogMessage::Type::Unknown) {
        throw std::runtime_error(
            std::string("Необработанное сообщение: ") + msg.message());
    }

    // если это не Unknown (а вдруг цепочка неполная) — передаём дальше
    LogHandler::handle(msg);
}
