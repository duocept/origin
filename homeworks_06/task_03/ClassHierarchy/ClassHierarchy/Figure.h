#pragma once
#ifndef FIGURE_H
#define FIGURE_H
#include <string>

class Figure {
protected:
    std::string name;

public:
    Figure(const std::string& name);
    virtual void print_info() const = 0;
    virtual ~Figure() = default;
};

#endif