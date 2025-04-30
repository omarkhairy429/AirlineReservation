#ifndef RESERVATION_DATABASE_UTILS_HPP
#define RESERVATION_DATABASE_UTILS_HPP

#include <vector>
#include <memory>
#include <string>
#include "json.hpp"
#include "Reservation.hpp"

using namespace std;
using json = nlohmann::json;

void loadReservations(vector<shared_ptr<Reservation>>& reservations, const string& filePath);

void saveReservations(const vector<shared_ptr<Reservation>>& reservations, const string& filePath);


#endif // RESERVATION_DATABASE_UTILS_HPP
