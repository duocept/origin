#ifndef GEOMETRYERROR_H
#define GEOMETRYERROR_H

#include <stdexcept>
#include <string>

class GeometryError : public std::domain_error {
public:
    explicit GeometryError(const std::string& msg)
        : std::domain_error(msg) {}
};

#endif