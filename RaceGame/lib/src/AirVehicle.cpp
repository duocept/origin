#include "AirVehicle.h"

double AirVehicle::time_for_distance(double distance_km) const {
    if (distance_km <= 0.0) return 0.0;
    const double effective_distance = distance_km * distance_multiplier(distance_km);
    return effective_distance / speed_kmh_;
}
