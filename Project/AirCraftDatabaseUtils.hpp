#ifndef AIRCRAFTDATABASEUTILS_HPP
#define AIRCRAFTDATABASEUTILS_HPP

#include <vector>
#include <memory>
#include <string>
#include "AirCraft.hpp"
#include "json.hpp"  
using json = nlohmann::json;

void loadAircraft(vector<std::shared_ptr<Aircraft>>& aircrafts, const std::string& filename);
void saveAircraft(const std::vector<std::shared_ptr<Aircraft>>& aircrafts, const std::string& filename);

#endif
