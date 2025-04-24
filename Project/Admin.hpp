#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "User.hpp"
#include "UserStruct.hpp"
#include "json.hpp"
#include <vector>
#include <string>
#include "Passenger.hpp"
#include <iostream>
#include <memory>  // Include for shared_ptr
#include "Flight.hpp"


class Admin : public User {
private:
    vector<shared_ptr<User>> users;
    vector<shared_ptr<Flight>> Flights;
    void loadUsers();
    void saveUsers();
    void loadFlights();
    void saveFlights();
    // string hashPassword(const string &password);
    // bool verifyPassword(const string &password, const string &hashedPassword);

public:
    // User
    bool Login(string userName, string password) override;
    bool addUser(string userName, string password);
    bool updateUser(string userName, string newPassword);
    bool deleteUser(string userName);
    bool logUser(string userName, string password);

    // Flight
    bool addFlight(string flightNumber, string origin, string destination, string depratureTime, string arrivalTime, string status);
    bool updateFlight(string flightNumber, string newOrigin, string newDestination,string newDepartureTime, string newArrivalTime, string newStatus); 
    bool deleteFlight(string flightNumber);
    
};

#endif