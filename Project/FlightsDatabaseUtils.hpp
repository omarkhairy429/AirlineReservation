#ifndef FLIGHT_DATABASE_UTILS_H
#define FLIGHT_DATABASE_UTILS_H

#include <vector>
#include <memory>
#include <string>
#include "json.hpp"
#include "Flight.hpp"

using namespace std;
using json = nlohmann::json;

void saveFlights(const vector<shared_ptr<Flight>>& Flights, const string& filename);
void loadFlights(vector<shared_ptr<Flight>>& Flights, const string& filename);

#endif 
