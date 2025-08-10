#pragma once
#include "AirVehicle.h"

class RACING_API Eagle : public AirVehicle {
public:
    Eagle() : AirVehicle("Орёл", 8.0) {}
protected:
    double distance_multiplier(double /*distance_km*/) const override {
        // Always 6% reduction
        return 0.94; // Wait! 6% reduction => multiplier 0.94? No: 6% off means multiply by 0.94.
    }
};
