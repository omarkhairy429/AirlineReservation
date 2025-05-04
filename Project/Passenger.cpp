#include "Passenger.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>
#include "Admin.hpp"

using namespace std;
using json = nlohmann::json;


//******************************************* Login  *******************************************/
bool Passenger::Login(string userName, string password) {
    Admin a1;
    return(a1.logUser(userName, password));
}

//******************************************* Deposit  *******************************************/
bool Passenger::deposit(double amount, string username) {
    if (amount <= 0) {
        cout << "Can't deposit zero or negative numbers" << endl;
        return false;
    }
    vector <shared_ptr<User>> users;
    loadUsers(users, "user.json");
    // Deposit will work when logged in so doesn't need to check if user exists
    auto it = find_if(users.begin(), users.end(), [&](const shared_ptr<User>& user) {
        auto passenger = dynamic_pointer_cast<Passenger>(user);
        return passenger->userName == username;
    });

    shared_ptr<Passenger> passenger = dynamic_pointer_cast<Passenger>(*it);
    passenger->balance = balance + amount;
    saveUsers(users, "user.json");
    return true;
}




//******************************************* Check In  *******************************************/
bool Passenger::checkIn(const string& reservationId, int user_id) {
    // Load data from JSON files
    vector<shared_ptr<Reservation>> reservations;
    vector<shared_ptr<CheckIn>> checks;
    vector<shared_ptr<User>> users;
    vector<shared_ptr<Flight>> flights;

    loadData<Reservation>(reservations, "reservations.json");
    loadData<CheckIn>(checks, "checkIn.json");
    loadUsers(users, "user.json");
    loadData<Flight>(flights, "Flights.json");

    // Find the reservation
    auto it = find_if(reservations.begin(), reservations.end(), [&](const shared_ptr<Reservation>& reservation) {
        return reservation->getReservationID() == reservationId && reservation->getPassengerID() == user_id;
    });

    if (it != reservations.end()) {
        // Reservation exists, proceed with check-in
        shared_ptr<Reservation> reservation = *it;

        // Retrieve passenger name from the users database
        string passengerName = "Unknown Passenger";
        auto userIt = find_if(users.begin(), users.end(), [&](const shared_ptr<User>& user) {
            auto passenger = dynamic_pointer_cast<Passenger>(user);
            return passenger && passenger->getUserId() == user_id;
        });
        if (userIt != users.end()) {
            auto passenger = dynamic_pointer_cast<Passenger>(*userIt);
            if (passenger) {
                passengerName = passenger->getUserName();
            }
        }

        // Retrieve flight details (origin, destination, departure time) from the flights database
        string origin = "Unknown Origin";
        string destination = "Unknown Destination";
        string departureDateTime = "Unknown Departure Time";
        auto flightIt = find_if(flights.begin(), flights.end(), [&](const shared_ptr<Flight>& flight) {
            return flight->getFlightNumber() == reservation->getFlightNumber();
        });
        if (flightIt != flights.end()) {
            origin = (*flightIt)->getOrigin();
            destination = (*flightIt)->getDestination();
            departureDateTime = (*flightIt)->getDepratureTime();
        }

        // Create a new CheckIn object
        CheckIn newCheckIn(
            reservation->getReservationID(),
            passengerName,
            reservation->getFlightNumber(),
            origin,
            destination,
            departureDateTime,
            reservation->getSeatNumber()
        );

        // Add the new check-in to the database
        checks.push_back(make_shared<CheckIn>(newCheckIn));
        saveData<CheckIn>(checks, "checkIn.json");

        newCheckIn.displayCheckInDetails(); // Display the check-in details
        return true;
    } else {
        return false;
    }
}

