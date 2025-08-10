#pragma once
#include "LandVehicle.h"

class RACING_API AllTerrainBoots : public LandVehicle {
public:
    AllTerrainBoots() : LandVehicle("Ботинки-вездеходы", 6.0, 60.0) {}
protected:
    double rest_duration_hours_for_stop(size_t rest_index) const override {
        // First: 10h, subsequent: 5h
        if (rest_index == 1) return 10.0;
        return 5.0;
    }
};
