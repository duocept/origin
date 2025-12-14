#include "LogMessage.h"

LogMessage::LogMessage(Type type, std::string message)
    : type_(type)
    , message_(std::move(message)) {
}

LogMessage::Type LogMessage::type() const {
    return type_;
}

const std::string& LogMessage::message() const {
    return message_;
}
