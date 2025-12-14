#include "Observers.h"

// WarningObserver
WarningObserver::WarningObserver(std::unique_ptr<LogCommand> command)
    : command_(std::move(command)) {
}

void WarningObserver::onWarning(const std::string& message) {
    if (command_) {
        command_->print("[Warning] " + message);
    }
}

// ErrorObserver
ErrorObserver::ErrorObserver(std::unique_ptr<LogCommand> command)
    : command_(std::move(command)) {
}

void ErrorObserver::onError(const std::string& message) {
    if (command_) {
        command_->print("[Error] " + message);
    }
}

// FatalErrorObserver
FatalErrorObserver::FatalErrorObserver(std::unique_ptr<LogCommand> consoleCommand,
    std::unique_ptr<LogCommand> fileCommand)
    : consoleCommand_(std::move(consoleCommand))
    , fileCommand_(std::move(fileCommand)) {
}

void FatalErrorObserver::onFatalError(const std::string& message) {
    const std::string full = "[Fatal] " + message;

    if (consoleCommand_) {
        consoleCommand_->print(full);
    }

    if (fileCommand_) {
        fileCommand_->print(full);
    }
}
