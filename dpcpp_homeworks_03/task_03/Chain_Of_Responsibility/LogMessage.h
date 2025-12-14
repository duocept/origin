#pragma once

#include <string>

class LogMessage {
public:
    enum class Type {
        Warning,
        Error,
        FatalError,
        Unknown
    };

    LogMessage(Type type, std::string message);

    Type type() const;
    const std::string& message() const;

private:
    Type type_;
    std::string message_;
};
