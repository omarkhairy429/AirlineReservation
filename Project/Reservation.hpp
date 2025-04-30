#ifndef RESERVATION_HPP
#define RESERVATION_HPP

#include <string>
#include "json.hpp"
using namespace std;

using json = nlohmann::json;

class Reservation {
private:
    int passengerID;
    string flightNumber;
    string seatNumber;
    string paymentMethod;
    string paymentDetails;

public:
    Reservation() = default;

    Reservation(int id, const std::string& flight, const std::string& seat, const std::string& method, const std::string& details)
        : passengerID(id), flightNumber(flight), seatNumber(seat), paymentMethod(method), paymentDetails(details) {}

    // Setters
    void setPassengerID(int id);
    void setFlightNumber(const string& flight);
    void setSeatNumber(const string& seat);
    void setPaymentMethod(const string& method);
    void setPaymentDetails(const string& details);

    // Getters
    int getPassengerID() const;
    string getFlightNumber() const;
    string getSeatNumber() const;
    string getPaymentMethod() const;
    //string getPaymentDetails() const;

    // Friend functions to handle JSON conversion
    friend void to_json(json& j, const Reservation& r) {
        j = json{
            {"passengerID", r.passengerID},
            {"flightNumber", r.flightNumber},
            {"seatNumber", r.seatNumber},
            {"paymentMethod", r.paymentMethod},
            {"paymentDetails", r.paymentDetails}
        };
    }

    friend void from_json(const json& j, Reservation& r) {
        j.at("passengerID").get_to(r.passengerID);
        j.at("flightNumber").get_to(r.flightNumber);
        j.at("seatNumber").get_to(r.seatNumber);
        j.at("paymentMethod").get_to(r.paymentMethod);
        j.at("paymentDetails").get_to(r.paymentDetails);
    }
};

#endif // RESERVATION_HPP
