#ifndef FLIGHT_ATTENDANT_HPP
#define FLIGHT_ATTENDANT_HPP

#include <string>
#include <memory>
#include "Flight.hpp"
#include <vector>
#include "FlightsDatabaseUtils.hpp"
#include "json.hpp"
using json = nlohmann::json;

using namespace std;

class FlightAttendant {
    private:
        string attendantID;
        string attendantName;
        string assignedFlightID;
    public:
    friend void to_json(json& j, const FlightAttendant& a) {
        j = json{
            {"attendantID", a.attendantID},
            {"attendantName", a.attendantName},
        };
    }
    
    friend void from_json(const json& j, FlightAttendant& a) {
        j.at("attendantID").get_to(a.attendantID);
        j.at("attendantName").get_to(a.attendantName);
    } 

    friend class Admin;
};

#endif