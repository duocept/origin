#include "LogSubject.h"

void LogSubject::addObserver(const std::shared_ptr<Observer>& observer) {
    observers_.push_back(observer); // храним как weak_ptr
}

void LogSubject::warning(const std::string& message) const {
    notify([&](Observer& obs) { obs.onWarning(message); });
}

void LogSubject::error(const std::string& message) const {
    notify([&](Observer& obs) { obs.onError(message); });
}

void LogSubject::fatalError(const std::string& message) const {
    notify([&](Observer& obs) { obs.onFatalError(message); });
}
