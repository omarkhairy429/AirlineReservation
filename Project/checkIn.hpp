#ifndef CHECKIN_HPP
#define CHECKIN_HPP

#include <iostream>
#include "json.hpp"
using namespace std;

using json = nlohmann::json;

class CheckIn {
    private:
        string reservationID;
        string passengerName;
        string flightNumber;
        string origin;
        string destination;
        string departureDateTime;
        string seatNumber;
    public:
        CheckIn() = default;

        
        CheckIn(string resID, string pName, string fNum, string orig, string dest, string depDateTime, string seatNum) 
            : reservationID(resID), passengerName(pName), flightNumber(fNum), origin(orig), destination(dest), departureDateTime(depDateTime), seatNumber(seatNum) {}

        void displayCheckInDetails() {
            cout << "Check-In Details:" << endl;
            cout << "Reservation ID: " << reservationID << endl;
            cout << "Passenger Name: " << passengerName << endl;
            cout << "Flight Number: " << flightNumber << endl;
            cout << "Origin: " << origin << endl;
            cout << "Destination: " << destination << endl;
            cout << "Departure Date and Time: " << departureDateTime << endl;
            cout << "Seat Number: " << seatNumber << endl;
        }

        /* Setters and Getters */
        void setReservationID(string resID) { reservationID = resID; }
        string getReservationID() { return reservationID; }
        void setPassengerName(string pName) { passengerName = pName; }
        string getPassengerName() { return passengerName; }
        void setFlightNumber(string fNum) { flightNumber = fNum; }
        string getFlightNumber() { return flightNumber; }
        void setOrigin(string orig) { origin = orig; }
        string getOrigin() { return origin; }
        void setDestination(string dest) { destination = dest; }
        string getDestination() { return destination; }
        void setDepartureDateTime(string depDateTime) { departureDateTime = depDateTime; }
        string getDepartureDateTime() { return departureDateTime; }
        void setSeatNumber(string seatNum) { seatNumber = seatNum; }
        string getSeatNumber() { return seatNumber; }

        friend void to_json(json& j, const CheckIn& c) {
            j = json{
                {"reservationID", c.reservationID},
                {"passengerName", c.passengerName},
                {"flightNumber", c.flightNumber},
                {"origin", c.origin},
                {"destination", c.destination},
                {"departureDateTime", c.departureDateTime},
                {"seatNumber", c.seatNumber},
            };
        }
        friend void from_json(const json& j, CheckIn& c) {
            j.at("reservationID").get_to(c.reservationID);
            j.at("passengerName").get_to(c.passengerName);
            j.at("flightNumber").get_to(c.flightNumber);
            j.at("origin").get_to(c.origin);
            j.at("destination").get_to(c.destination);
            j.at("departureDateTime").get_to(c.departureDateTime);
            j.at("seatNumber").get_to(c.seatNumber);
        }
};


#endif