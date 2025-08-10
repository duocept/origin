#pragma once
#include "LandVehicle.h"

class RACING_API Camel : public LandVehicle {
public:
    Camel() : LandVehicle("Верблюд", 10.0, 30.0) {}
protected:
    double rest_duration_hours_for_stop(size_t rest_index) const override {
        // First rest 5h, all subsequent 8h
        if (rest_index == 1) return 5.0;
        return 8.0;
    }
};
