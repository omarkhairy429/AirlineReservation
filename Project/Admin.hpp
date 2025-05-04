#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "Passenger.hpp"
#include "User.hpp"
#include "UserStruct.hpp"
#include "json.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <memory>  
#include "Flight.hpp"
#include "AirCraft.hpp"
#include "UserDatabaseUtils.hpp"
#include "Pilot.hpp"
#include "FlightAttendant.hpp"
#include "DatabaseUtils.hpp"



class Admin : public User {
private:
    vector<shared_ptr<User>> users;
    vector<shared_ptr<Flight>> Flights;
    vector<shared_ptr<Pilot>> pilots;
    vector<shared_ptr<FlightAttendant>> flightAttendants;
    vector<shared_ptr<Aircraft>> aircrafts;

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
    bool addFlight(string flightNumber, string origin, string destination, string depratureTime, string arrivalTime,int seats, string status, double price);
    bool updateFlight(string flightNumber, string newOrigin, string newDestination,string newDepartureTime, string newArrivalTime,int newSeats, string newStatus, double newPrice); 
    bool deleteFlight(string flightNumber);

    // Crew
    bool addPilot(string pilotName, string pilotID);
    bool addFlightAttendant(string name, string id);
    bool assignCrew(string captainID, string attendantID, string flightID);

    // Aircraft
    bool addAircraft(string model, string id, int capacity, double maxSpeed);
    bool assignAircraftToFlight(string aircraftID, string flightID);
    friend class AdminMode; // Allow AdminMode to access private members of Admin
};

#endif