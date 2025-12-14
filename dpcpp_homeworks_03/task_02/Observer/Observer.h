#pragma once

#include <string>

class Observer {
public:
    virtual ~Observer() = default;

    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};
