#ifndef BOOKINGAGENT_HPP
#define BOOKINGAGENT_HPP

#include "User.hpp"
#include "Passenger.hpp"
#include "Flight.hpp"
#include <vector>
#include <memory>
#include "Reservation.hpp"
#include "UserDatabaseUtils.hpp"
#include "DatabaseUtils.hpp"




using namespace std;

class BookingAgent: public User {
    private:
        vector<shared_ptr<Reservation>> reservations;
        vector<shared_ptr<User>> users;
        vector<shared_ptr<Flight>> Flights;
    
    public:

        bool Login(string userName, string password);
        void searchFlights(string origin, string destination, string depratureDate);
        bool bookFlight(int passengerID, string flightNumber, string seat, string paymentMethod, string paymentDetails, string reservationID);
        bool cancelReservation(string reservationID);

};

#endif