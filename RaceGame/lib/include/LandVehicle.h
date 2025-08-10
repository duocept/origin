#pragma once
#include "Vehicle.h"
#include <utility> // std::move

class RACING_API LandVehicle : public Vehicle {
public:
    LandVehicle(std::string name, double speed_kmh, double move_time_before_rest_h)
        : Vehicle(std::move(name)), speed_kmh_(speed_kmh), move_time_before_rest_h_(move_time_before_rest_h) {}

    double speed() const override { return speed_kmh_; }
    bool is_land() const override { return true; }
    bool is_air() const override { return false; }

    double time_for_distance(double distance_km) const override;

protected:
    // rest index starts from 1 (first rest is 1)
    virtual double rest_duration_hours_for_stop(size_t rest_index) const = 0;

    double speed_kmh_;
    double move_time_before_rest_h_;
};
