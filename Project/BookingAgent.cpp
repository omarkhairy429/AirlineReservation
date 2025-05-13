#include <iostream>
#include "BookingAgent.hpp"
#include "fstream"
#include <algorithm>

//****************************************** Booking Agent Login ******************************************/
bool BookingAgent::Login(string userName, string password) {
    if (userName == "agent" && password == "12345") {
        this->userName = userName;
        this->password = password;
        return true;
    }
    return false;

    
}




/*************************************** Booking search Flight  ******************************************/
bool BookingAgent::searchFlights(string origin, string destination, string depratureDate) {
    loadData<Flight>(Flights, "Flights.json");
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
            cout << "   Price: " << flight->price << endl;
        }
    }
    if (counter == 0) {
        cout << "There is no available Flights right now -_-" << endl;
        return false;
    }
    return true;
}






/****************************************** Booking a Flight ******************************************/
bool BookingAgent::bookFlight(int passengerID, string flightNumber, string seat, string paymentMethod, string paymentDetails, string reservationID) {
    loadUsers(users, "user.json");
    loadData<Flight>(Flights, "Flights.json");
    loadData<Reservation>(reservations, "reservations.json");

    auto user_it = find_if(users.begin(), users.end(), [&](const shared_ptr<User> user) {
        auto u = dynamic_pointer_cast<Passenger>(user);
        return (u->getUserId() == passengerID);
    });
    if (user_it == users.end()) {
        cout << "Passenger ID not found" << endl;
        return false;
    }

    auto flight_it = find_if(Flights.begin(), Flights.end(), [&](const shared_ptr<Flight> flight) {
        return (flight->flightNumber == flightNumber);
    });

    if (flight_it == Flights.end()) {
        cout << "Flight number not found" << endl;
        return false;
    }
    else if (((*flight_it)->availableSeats) == 0) {
        cout << "There is no available seats" << endl;
        return false;
    }

    if (seat.length() != 3) {
        cout << "Invalid seat form" << endl;
        cout << "You should enter seat 3 char first two are seat numbers and the third is seat character from A to F" << endl;
        return false;
    }
    else if(!isdigit(seat[0]) || !isdigit(seat[1])) {
        cout << "Invalid seat form" << endl;
        cout << "You should enter seat 3 char first two are seat numbers and the third is seat character from A to F" << endl;
        return false;
    }
    int rowNumber = stoi(seat.substr(0, 2));
    if (rowNumber > (*flight_it)->total_seats) {
        cout << "The trip have seats with id smaller than this" << endl;
        return false;
    }

    auto isTaken = find_if(reservations.begin(), reservations.end(), 
    [&seat](const shared_ptr<Reservation>& res) {
        return res->getSeatNumber() == seat;
    });
    if (isTaken != reservations.end()) {
        cout << "This seat is taken" << endl;
        return false;
    }

    auto idExists = find_if(reservations.begin(), reservations.end(),
    [&reservationID](const shared_ptr<Reservation>& res) {
        return res->reservationID == reservationID;
    });
    if (idExists != reservations.end()) {
        cout << "Reservation ID already exists" << endl;
        return false;
    }
    /** price **/
    auto passengerIt = dynamic_pointer_cast<Passenger>(*user_it);
    if( (passengerIt->balance) < (*flight_it)->price) {
        cout << "You don't have enough money" << endl;
        return false;
    }
    // Update passenger's balance and loyalty points
    passengerIt->loyalty_points += 10;
    passengerIt->balance = (passengerIt->balance) - ((*flight_it)->price);
    (*flight_it)->totalRevenue = (*flight_it)->totalRevenue + ((*flight_it)->price);


    reservations.emplace_back(std::make_shared<Reservation>(passengerID, flightNumber, seat, paymentMethod, paymentDetails, reservationID));

    Payment* payment = PaymentFactory::createPayment(paymentMethod);
    if (payment) {
        cout << "Payment method: " << payment->getType() << endl;
        delete payment; 
    } else {
        cout << "Invalid payment method" << endl;
        return false;
    }

    (*flight_it)->availableSeats--;
    saveData<Reservation>(reservations, "reservations.json");
    saveData<Flight>(Flights, "Flights.json");
    saveUsers(users, "user.json");
    return true;
}



/****************************************** Modify Reservation ******************************************/
bool BookingAgent::modifyReservation(string reservationID, string newSeat, string newPaymentMethod, string newPaymentDetails) {
    loadUsers(users, "user.json");
    loadData<Flight>(Flights, "Flights.json");
    loadData<Reservation>(reservations, "reservations.json");

    // Find the reservation by ID
    auto reservation_it = find_if(reservations.begin(), reservations.end(), [&](const shared_ptr<Reservation>& res) {
        return res->reservationID == reservationID;
    });

    if (reservation_it == reservations.end()) {
        cout << "Reservation ID not found" << endl;
        return false;
    }

    // Extract flight number and passenger ID from the reservation
    string flightNumber = (*reservation_it)->getFlightNumber();
    int passengerID = (*reservation_it)->getPassengerID();

    // Find the flight by flight number
    auto flight_it = find_if(Flights.begin(), Flights.end(), [&](const shared_ptr<Flight>& flight) {
        return flight->flightNumber == flightNumber;
    });

    if (flight_it == Flights.end()) {
        cout << "Flight number not found in reservations" << endl;
        return false;
    }

    // Validate the new seat
    if (newSeat.length() != 3 || !isdigit(newSeat[0]) || !isdigit(newSeat[1]) || !(newSeat[2] >= 'A' && newSeat[2] <= 'F')) {
        cout << "Invalid seat format. Seat must be in the format '12A' (two digits followed by a letter A-F)." << endl;
        return false;
    }

    int rowNumber = stoi(newSeat.substr(0, 2));
    if (rowNumber > (*flight_it)->total_seats) {
        cout << "The flight does not have seats with this row number." << endl;
        return false;
    }

    // Check if the new seat is already taken
    auto isTaken = find_if(reservations.begin(), reservations.end(), [&](const shared_ptr<Reservation>& res) {
        return res->getSeatNumber() == newSeat && res->getFlightNumber() == flightNumber;
    });

    if (isTaken != reservations.end()) {
        cout << "The new seat is already taken." << endl;
        return false;
    }

    // Update the reservation details
    (*reservation_it)->setSeatNumber(newSeat);
    (*reservation_it)->setPaymentMethod(newPaymentMethod);
    (*reservation_it)->setPaymentDetails(newPaymentDetails);

    // Save the updated data
    saveData<Reservation>(reservations, "reservations.json");
    return true;
}



/***************************************************** Cancel Reservation ******************************************************/
bool BookingAgent::cancelReservation(string reservationID) {
    loadUsers(users, "user.json");
    loadData<Flight>(Flights, "Flights.json");
    loadData<Reservation>(reservations, "reservations.json");

    // Find the reservation by ID
    auto reservation_it = find_if(reservations.begin(), reservations.end(), [&](const shared_ptr<Reservation>& res) {
        return res->reservationID == reservationID;
    });

    if (reservation_it == reservations.end()) {
        cout << "Reservation ID not found" << endl;
        return false;
    }

    // Extract flight number and passenger ID from the reservation
    string flightNumber = (*reservation_it)->getFlightNumber();
    int passengerID = (*reservation_it)->getPassengerID();

    // Find the flight by flight number
    auto flight_it = find_if(Flights.begin(), Flights.end(), [&](const shared_ptr<Flight>& flight) {
        return flight->flightNumber == flightNumber;
    });

    if (flight_it == Flights.end()) {
        cout << "Flight number not found in reservations" << endl;
        return false;
    }

    // Find the passenger by ID
    auto user_it = find_if(users.begin(), users.end(), [&](const shared_ptr<User>& user) {
        auto passenger = dynamic_pointer_cast<Passenger>(user);
        return passenger && passenger->getUserId() == passengerID;
    });

    if (user_it == users.end()) {
        cout << "Passenger ID not found in reservations" << endl;
        return false;
    }

    // Refund the passenger and update the flight
    auto passenger = dynamic_pointer_cast<Passenger>(*user_it);
    if (!passenger) {
        cout << "Error: User is not a Passenger" << endl;
        return false;
    }

    double price = (*flight_it)->price;
    passenger->balance += price; // Refund the price to the passenger
    (*flight_it)->availableSeats++; // Increase available seats by 1
    (*flight_it)->totalRevenue -= price; // Decrease total revenue by the price
    passenger->loyalty_points -= 10; // Decrease loyalty points by 10

    // Remove the reservation
    reservations.erase(reservation_it);

    // Save the updated data
    saveData<Reservation>(reservations, "reservations.json");
    saveData<Flight>(Flights, "Flights.json");
    saveUsers(users, "user.json");

    cout << "Reservation canceled successfully!" << endl;
    return true;
}


