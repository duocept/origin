#include "Race.h"
#include <algorithm>

bool Race::can_register(const Vehicle& v) const {
    if (type_ == RaceType::Land && !v.is_land()) return false;
    if (type_ == RaceType::Air  && !v.is_air())  return false;
    // Mixed accepts both
    return registered_names_.find(v.name()) == registered_names_.end();
}

bool Race::register_vehicle(std::shared_ptr<Vehicle> v) {
    if (!v) return false;
    if (!can_register(*v)) return false;
    registered_names_.insert(v->name());
    vehicles_.push_back(std::move(v));
    return true;
}

std::vector<RaceResult> Race::start(double distance_km) const {
    std::vector<RaceResult> results;
    results.reserve(vehicles_.size());
    for (const auto& v : vehicles_) {
        results.push_back({v->name(), v->time_for_distance(distance_km)});
    }
    std::sort(results.begin(), results.end(), [](const RaceResult& a, const RaceResult& b){
        return a.time_hours < b.time_hours;
    });
    return results;
}
