#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "Passenger.hpp"
#include "User.hpp"
#include "UserStruct.hpp"
#include "json.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <memory>  // Include for shared_ptr
#include "Flight.hpp"
#include "UserDatabaseUtils.hpp"
#include "FlightsDatabaseUtils.hpp"
#include "Pilot.hpp"
#include "FlightAttendant.hpp"



class Admin : public User {
private:
    vector<shared_ptr<User>> users;
    vector<shared_ptr<Flight>> Flights;

    // string hashPassword(const string &password);
    // bool verifyPassword(const string &password, const string &hashedPassword);

public:
    // User
    bool Login(string userName, string password) override;
    bool addUser(string userName, string password, int user_id, string email, int loyalty_points);
    bool updateUser(string userName, string newPassword);
    bool deleteUser(string userName);
    bool logUser(string userName, string password);

    // Flight
    bool addFlight(string flightNumber, string origin, string destination, string depratureTime, string arrivalTime,int seats, string status);
    bool updateFlight(string flightNumber, string newOrigin, string newDestination,string newDepartureTime, string newArrivalTime,int newSeats, string newStatus); 
    bool deleteFlight(string flightNumber);
    
};

#endif