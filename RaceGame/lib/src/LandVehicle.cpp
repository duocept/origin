#include "LandVehicle.h"
#include <cmath>

double LandVehicle::time_for_distance(double distance_km) const {
    if (distance_km <= 0.0) return 0.0;

    // Pure moving time without rests
    const double moving_time = distance_km / speed_kmh_;

    // How many full "move segments" fit into moving_time
    // Each segment equals move_time_before_rest_h_ hours
    if (move_time_before_rest_h_ <= 0.0) {
        // No rests if move_time_before_rest_h_ <= 0, fallback
        return moving_time;
    }

    double segments = moving_time / move_time_before_rest_h_;
    size_t full_segments = static_cast<size_t>(std::floor(segments));

    // If exactly on a rest boundary (e.g., moving_time == n * move_time_before_rest), there is no rest after finish
    bool finishes_on_boundary = std::fabs(segments - full_segments) < 1e-12;
    size_t rests = finishes_on_boundary ? (full_segments == 0 ? 0 : full_segments - 1) : full_segments;

    double total_rest_time = 0.0;
    for (size_t i = 1; i <= rests; ++i) {
        total_rest_time += rest_duration_hours_for_stop(i);
    }

    return moving_time + total_rest_time;
}
