#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include <iostream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

class Flight {
private:
    string flightNumber;
    string origin;
    string destination;
    string depratureTime;
    string arrivalTime;
    string status;

public:
    Flight() = default;
    Flight(string flightNumber, string origin, string destination, string depratureTime, string arrivalTime, string status) :
        flightNumber(flightNumber), origin(origin), destination(destination),
        depratureTime(depratureTime), arrivalTime(arrivalTime), status(status) {
    }

    // Friend functions for JSON serialization
    friend void to_json(json& j, const Flight& f) {
        j = json{
            {"flightNumber", f.flightNumber},
            {"origin", f.origin},
            {"destination", f.destination},
            {"depratureTime", f.depratureTime},
            {"arrivalTime", f.arrivalTime},
            {"status", f.status}
        };
    }

    friend void from_json(const json& j, Flight& f) {
        j.at("flightNumber").get_to(f.flightNumber);
        j.at("origin").get_to(f.origin);
        j.at("destination").get_to(f.destination);
        j.at("depratureTime").get_to(f.depratureTime);
        j.at("arrivalTime").get_to(f.arrivalTime);
        j.at("status").get_to(f.status);
    }

    friend class Admin;
    friend class BookingAgent;
};

#endif