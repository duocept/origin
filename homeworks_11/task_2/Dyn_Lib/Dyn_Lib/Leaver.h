#pragma once
#include <string>
#ifdef LEAVELIBRARYDYNAMIC_EXPORTS
#define LEAVELIBRARY_API __declspec(dllexport)
#else
#define LEAVELIBRARY_API __declspec(dllimport)
#endif

namespace leave {

    class Leaver {
    public:
        LEAVELIBRARY_API std::string leave(const std::string& name) const;
    };

}