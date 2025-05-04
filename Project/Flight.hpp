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
    int total_seats;
    int availableSeats;
    double totalRevenue;
    double price;

public:
    Flight() = default;
    Flight(string flightNumber, string origin, string destination, string depratureTime, string arrivalTime,int seats ,string status, double price) :
        flightNumber(flightNumber), origin(origin), destination(destination),
        depratureTime(depratureTime), arrivalTime(arrivalTime), total_seats(seats) ,status(status), availableSeats(seats), price(price) {
    }

    // Friend functions for JSON serialization
    friend void to_json(json& j, const Flight& f) {
        j = json{
            {"flightNumber", f.flightNumber},
            {"origin", f.origin},
            {"destination", f.destination},
            {"depratureTime", f.depratureTime},
            {"arrivalTime", f.arrivalTime},
            {"status", f.status},
            {"Seats", f.total_seats},
            {"Available seats", f.availableSeats},
            {"Price", f.price},
            {"Revenue", f.totalRevenue}

        };
    }

    friend void from_json(const json& j, Flight& f) {
        j.at("flightNumber").get_to(f.flightNumber);
        j.at("origin").get_to(f.origin);
        j.at("destination").get_to(f.destination);
        j.at("depratureTime").get_to(f.depratureTime);
        j.at("arrivalTime").get_to(f.arrivalTime);
        j.at("status").get_to(f.status);
        j.at("Seats").get_to(f.total_seats);
        j.at("Available seats").get_to(f.availableSeats);
        j.at("Price").get_to(f.price);
        j.at("Revenue").get_to(f.totalRevenue);
        
    }

    friend class Admin;
    friend class BookingAgent;
    friend class crewMember;
    friend class BookingAgent;
    friend class AgentMode;
};

#endif