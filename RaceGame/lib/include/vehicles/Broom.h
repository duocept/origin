#pragma once
#include "AirVehicle.h"
#include <cmath>
#include <algorithm> // std::max

class RACING_API Broom : public AirVehicle {
public:
    Broom() : AirVehicle("Метла", 20.0) {}
protected:
    double distance_multiplier(double distance_km) const override {
        // Increases by 1% per each 1000 units; example: 5600 => 5% reduction
        const int thousands = static_cast<int>(std::floor(distance_km / 1000.0));
        const double reduction = std::max(0, thousands) * 0.01;
        const double multiplier = 1.0 - reduction;
        // Clamp to a reasonable lower bound (>0)
        return multiplier > 0.0 ? multiplier : 0.0;
    }
};
