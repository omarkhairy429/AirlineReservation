#ifndef FLIGHT_ATTENDANT_DATABASE_UTILS_HPP
#define FLIGHT_ATTENDANT_DATABASE_UTILS_HPP

#include "FlightAttendant.hpp"
#include <vector>
#include <memory>
#include <string>

using json = nlohmann::json;  // Assuming you're using the nlohmann/json library for JSON handling

// Function to save FlightAttendant objects to a JSON file
void saveFlightAttendants(const std::vector<std::shared_ptr<FlightAttendant>>& attendants, const std::string& filename);

// Function to load FlightAttendant objects from a JSON file
void loadFlightAttendants(std::vector<std::shared_ptr<FlightAttendant>>& attendants, const std::string& filename);

#endif // FLIGHT_ATTENDANT_DATABASE_UTILS_HPP
