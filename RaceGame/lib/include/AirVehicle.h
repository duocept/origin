#pragma once
#include "Vehicle.h"
#include <utility> // std::move

class RACING_API AirVehicle : public Vehicle {
public:
    AirVehicle(std::string name, double speed_kmh)
        : Vehicle(std::move(name)), speed_kmh_(speed_kmh) {}

    double speed() const override { return speed_kmh_; }
    bool is_land() const override { return false; }
    bool is_air() const override { return true; }

    double time_for_distance(double distance_km) const override;

protected:
    // Returns fraction to multiply the distance by (e.g., 0.95 means 5% reduction)
    virtual double distance_multiplier(double distance_km) const = 0;

    double speed_kmh_;
};
