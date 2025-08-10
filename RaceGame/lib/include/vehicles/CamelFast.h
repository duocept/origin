#pragma once
#include "LandVehicle.h"

class RACING_API CamelFast : public LandVehicle {
public:
    CamelFast() : LandVehicle("Верблюд-быстроход", 40.0, 10.0) {}
protected:
    double rest_duration_hours_for_stop(size_t rest_index) const override {
        // 1st: 5h, 2nd: 6.5h, subsequent: 8h
        if (rest_index == 1) return 5.0;
        if (rest_index == 2) return 6.5;
        return 8.0;
    }
};
