#include <iostream>
#include "BookingAgent.hpp"
#include "fstream"
#include <algorithm>

bool BookingAgent::Login(string userName, string password) {
    if (userName == "agentUser" && password == "12345") {
        this->userName = userName;
        this->password = password;
        return true;
    }
    return false;

    
}


/******************************** Start of Booking Agent Flight Operations  **************************************************/

/* Search in Flights database  */
void BookingAgent::searchFlights(string origin, string destination, string depratureDate) {
    loadFlights(Flights, "Flights.json");
    int counter = 0;
    for(const auto& flight : Flights) {
        // Example output
        if (flight->origin == origin && flight->destination == destination && (flight->depratureTime).substr(0,10) == depratureDate) {
            counter++;
            cout << counter << ". " << "Flight Number: " << flight->flightNumber << endl;
            cout << "   Deprature: " << flight->depratureTime << endl;
            cout << "   Arrival: " << flight->arrivalTime<< endl;
            cout << "   Available seats: " << flight->availableSeats << endl;
            cout << "   Aircraft: " << endl;
            cout << "   Price: " << endl;
            // Available seats to be added
            // Price to be added
        }
    }
    if (counter == 0) {
        cout << "There is no available Flights right now -_-" << endl;
    }
}


/******************************** End of Booking Agent Flight Operations  **************************************************/







/****************************************** Booking Agent and User Relation ******************************************/

bool BookingAgent::bookFlight(int passengerID, string flightNumber, string seat, string paymentMethod, string paymentDetails) {
    loadUsers(users, "user.json");
    loadFlights(Flights, "Flights.json");
    loadReservations(reservations, "reservations.json");

    /* PassengerID doesn't exist */
    auto user_it = find_if(users.begin(), users.end(), [&](const shared_ptr<User> user) {
        auto u = dynamic_pointer_cast<Passenger>(user);
        return (u->getUserId() == passengerID);
    });
    if (user_it == users.end()) {
        cout << "Passenger ID not found" << endl;
        return false;
    }
    
    /* Flight number doesn't exits */
    auto flight_it = find_if(Flights.begin(), Flights.end(), [&](const shared_ptr<Flight> flight) {
        return (flight->flightNumber == flightNumber);
    });

    // Flight doesn't exist
    if (flight_it == Flights.end()) {
        cout << "Flight number not found" << endl;
        return false;
    }

    // No available seats
    else if (((*flight_it)->availableSeats) == 0) {
        cout << "There is no available seats" << endl;
        return false;
    }

    /* Seat doesn't exist */
    if (seat.length() != 3) {
        cout << "Invalid seat form" << endl;
        cout << "You should enter seat 3 char first two are seat numbers and the third is seat character from A to F" << endl;
        return false;
    }
    else if(!isdigit(seat[0]) || !isdigit(seat[1])) {  // Corrected this line
        cout << "Invalid seat form" << endl;
        cout << "You should enter seat 3 char first two are seat numbers and the third is seat character from A to F" << endl;
        return false;
    }
    int rowNumber = stoi(seat.substr(0, 2));
    if (rowNumber > (*flight_it)->total_seats) {
        cout << "The trip have seats with id smaller than this" << endl;
        return false;
    }

    /* Seat is taken */
    auto isTaken = find_if(reservations.begin(), reservations.end(), 
    [&seat](const shared_ptr<Reservation>& res) {
        return res->getSeatNumber() == seat;
    });
    if (isTaken != reservations.end()) {
        cout << "This seat is taken" << endl;
        return false;
    }
    reservations.emplace_back(std::make_shared<Reservation>(passengerID, flightNumber, seat, paymentMethod, paymentDetails));

    // Number of available seats is decreased by 1
    (*flight_it)->availableSeats--;
    saveReservations(reservations, "reservations.json");
    saveFlights(Flights, "Flights.json");
    return true;
}

