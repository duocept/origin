#pragma once
#include <vector>
#include <memory>
#include <string>
#include <unordered_set>
#include "racing_export.h"
#include "RaceType.h"
#include "Vehicle.h"

struct RACING_API RaceResult {
    std::string vehicle_name;
    double time_hours;
};

class RACING_API Race {
public:
    explicit Race(RaceType type) : type_(type) {}

    RaceType type() const { return type_; }

    bool can_register(const Vehicle& v) const;
    bool register_vehicle(std::shared_ptr<Vehicle> v);
    size_t participants_count() const { return vehicles_.size(); }

    std::vector<RaceResult> start(double distance_km) const;

private:
    RaceType type_;
    std::vector<std::shared_ptr<Vehicle>> vehicles_;
    std::unordered_set<std::string> registered_names_;
};
