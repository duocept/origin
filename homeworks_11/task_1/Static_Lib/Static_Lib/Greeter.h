#pragma once
#include <string>

namespace greet {

    class Greeter {
    public:
        std::string greet(const std::string& name) const;
    };

}