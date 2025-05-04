#ifndef PASSENGER_MODE_HPP
#define PASSENGER_MODE_HPP
#include <string>
#include "Passenger.hpp" 
#include "BookingAgent.hpp"
#include <fstream>
#include "UserDatabaseUtils.hpp"



class PassengerMode {
public:
    void startPassengerMode();  // Function to start the passenger mode
    // Function to chekcIN
    // Function to view his reservations 
    // and thats it for now

private:
    void bookFlight(Passenger& passenger);  // Function to book a flight
    void searchFlights(Passenger& passenger);  // Function to search for flights
    void viewReservations(Passenger& passenger);  // Function to view reservations
    void checkIn(Passenger& passenger);  // Function to check in for a flight
    void depositMoney(Passenger& passenger);  // Function to deposit money

};

#endif // PASSENGER_MODE_HPP
