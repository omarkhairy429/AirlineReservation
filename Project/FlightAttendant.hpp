#ifndef FLIGHT_ATTENDANT_HPP
#define FLIGHT_ATTENDANT_HPP

#include <string>
#include <memory>
#include "Flight.hpp"
#include <vector>
#include "DatabaseUtils.hpp"
#include "json.hpp"
using json = nlohmann::json;

using namespace std;

class FlightAttendant {
private:
    string attendantID;
    string attendantName;
    string assignedFlightID;

public:
    // Default Constructor
    FlightAttendant() = default;

    // Parameterized Constructor
    FlightAttendant(const string& id, const string& name, const string& flightID)
        : attendantID(id), attendantName(name), assignedFlightID(flightID) {}

    // Getters
    string getAttendantID() const { return attendantID; }
    string getAttendantName() const { return attendantName; }
    string getAssignedFlightID() const { return assignedFlightID; }

    // Setters
    void setAttendantID(const string& id) { attendantID = id; }
    void setAttendantName(const string& name) { attendantName = name; }
    void setAssignedFlightID(const string& flightID) { assignedFlightID = flightID; }

    // Friend functions for JSON serialization
    friend void to_json(json& j, const FlightAttendant& a) {
        j = json{
            {"attendantID", a.attendantID},
            {"attendantName", a.attendantName}
        };
    }

    friend void from_json(const json& j, FlightAttendant& a) {
        j.at("attendantID").get_to(a.attendantID);
        j.at("attendantName").get_to(a.attendantName);
    }

    // Friend classes
    friend class Admin;
};

#endif