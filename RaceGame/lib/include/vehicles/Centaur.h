#pragma once
#include "LandVehicle.h"

class RACING_API Centaur : public LandVehicle {
public:
    Centaur() : LandVehicle("Кентавр", 15.0, 8.0) {}
protected:
    double rest_duration_hours_for_stop(size_t /*rest_index*/) const override {
        // Always 2h
        return 2.0;
    }
};
