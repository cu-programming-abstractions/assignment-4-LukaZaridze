#include "disasterplanning.h"
#include "error.h"
#include "set.h"
#include "map.h"
#include "Demos/optional.h"

Optional<Set<std::string>>
placeEmergencySupplies(const Map<std::string, Set<std::string>>& roadNetwork,
                       int numCities) {
    if (numCities < 0) {
        error(std::string("Number of cities cannot be negative."));
        return Optional<Set<std::string>>();
    }

    Set<std::string> supplyLocations;
    Set<std::string> visited;

    auto isAdjacentToSupplyCity = [&](const std::string& city) -> bool {
        const Set<std::string>& neighbors = roadNetwork.get(city);
        for (const std::string& neighbor : neighbors) {
            if (supplyLocations.contains(neighbor)) {
                return true;
            }
        }
        return false;
    };

    Set<std::string> allCities;
    for (const std::string& city : roadNetwork.keys()) {
        allCities.add(city);
    }

    for (const std::string& city : allCities) {
        if (visited.contains(city) || isAdjacentToSupplyCity(city)) {
            continue;
        }

        if (supplyLocations.size() < static_cast<size_t>(numCities)) {
            supplyLocations.add(city);
            visited.add(city);

            const Set<std::string>& neighbors = roadNetwork.get(city);
            for (const std::string& neighbor : neighbors) {
                visited.add(neighbor);
            }
        }
    }

    if (supplyLocations.size() <= static_cast<size_t>(numCities)) {
        return Optional<Set<std::string>>(supplyLocations);
    } else {
        return Optional<Set<std::string>>();
    }
}


