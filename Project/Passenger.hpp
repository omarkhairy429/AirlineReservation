#ifndef PASSENGER_HPP
#define PASSENGER_HPP

#include "User.hpp"
#include <vector>

class Admin;

class Passenger : public User {
private:

public:
    Passenger() = default;
    Passenger(string userName, string password): User(userName, password) {}
    bool Login(std::string userName, std::string password) override;
    void searchFlights(string origin, string destination, string depratureDate);
    
};

#endif
