#include "Reservation.hpp"

// Setters
void Reservation::setPassengerID(int id) {
    passengerID = id;
}

void Reservation::setFlightNumber(const string& flight) {
    flightNumber = flight;
}

void Reservation::setSeatNumber(const string& seat) {
    seatNumber = seat;
}

void Reservation::setPaymentMethod(const string& method) {
    paymentMethod = method;
}

void Reservation::setPaymentDetails(const string& details) {
    paymentDetails = details;
}

void Reservation::setReservationID(const string& reservationID) {
    this->reservationID = reservationID;
}

// Getters
int Reservation::getPassengerID() const {
    return passengerID;
}

string Reservation::getFlightNumber() const {
    return flightNumber;
}

string Reservation::getSeatNumber() const {
    return seatNumber;
}

string Reservation::getPaymentMethod() const {
    return paymentMethod;
}

string Reservation:: getReservationID() const {
    return reservationID;
}


