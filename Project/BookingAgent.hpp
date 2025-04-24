#ifndef BOOKINGAGENT_HPP
#define BOOKINGAGENT_HPP

#include "User.hpp"
#include "Flight.hpp"
#include <vector>
#include <memory>

using namespace std;

class BookingAgent: public User {
    private:
        void loadFlights();
        void saveFlights();
    public:
        vector<shared_ptr<Flight>> Flights;
        bool Login(string userName, string password);
        void searchFlights(string origin, string destination, string depratureDate);

};

#endif