#pragma once
#include <string>
#include "racing_export.h"
#include <utility> // std::move

class RACING_API Vehicle {
public:
    explicit Vehicle(std::string name) : name_(std::move(name)) {}
    virtual ~Vehicle() = default;

    const std::string& name() const { return name_; }
    virtual double speed() const = 0; // km/h

    // Calculate total race time in hours for given distance in km
    virtual double time_for_distance(double distance_km) const = 0;

    // Type helpers
    virtual bool is_land() const = 0;
    virtual bool is_air() const = 0;

protected:
    std::string name_;
};
