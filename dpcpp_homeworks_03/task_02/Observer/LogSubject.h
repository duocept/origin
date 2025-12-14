#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Observer.h"

// Наблюдаемый класс
class LogSubject {
public:
    // добавляем НЕ владеющий указатель: храним weak_ptr
    void addObserver(const std::shared_ptr<Observer>& observer);

    void warning(const std::string& message) const;
    void error(const std::string& message) const;
    void fatalError(const std::string& message) const;

private:
    template <typename Func>
    void notify(Func func) const;

    // mutable, чтобы можно было чистить список в const-методах
    mutable std::vector<std::weak_ptr<Observer>> observers_;
};

// Шаблонный метод должен быть реализован в .h
template <typename Func>
void LogSubject::notify(Func func) const {
    auto it = observers_.begin();
    while (it != observers_.end()) {
        if (auto obs = it->lock()) {
            func(*obs);
            ++it;
        }
        else {
            // Наблюдатель уже разрушен — удаляем weak_ptr
            it = observers_.erase(it);
        }
    }
}

