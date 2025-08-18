#include "Greeter.h"

namespace greet {

    std::string Greeter::greet(const std::string& name) const {
        return "Здравствуйте, " + name + "!";
    }

}