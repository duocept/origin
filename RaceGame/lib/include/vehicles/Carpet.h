#pragma once
#include "AirVehicle.h"

class RACING_API Carpet : public AirVehicle {
public:
    Carpet() : AirVehicle("Ковёр-самолёт", 10.0) {}
protected:
    double distance_multiplier(double distance_km) const override {
        // <1000: 0% reduction; <5000: 3%; <10000: 10%; >=10000: 5%
        if (distance_km < 1000.0) return 1.0;
        if (distance_km < 5000.0) return 0.97;
        if (distance_km < 10000.0) return 0.90;
        return 0.95;
    }
};
