#include "Admin.hpp"
#include <fstream>
#include <algorithm>


using namespace std;
using json = nlohmann::json;


/* Start of Admin User relation */

// Admin logs in
bool Admin::Login(string userName, string password) {
    return userName == "adminUser" && password == "12345";
}

// Admin logs a user
bool Admin::addUser(string userName, string password, int user_id, string email, int loyalty_points) {
    loadUsers(users, "user.json");

    // Check if the user already exists
    auto it = find_if(users.begin(), users.end(), [&](const shared_ptr<User> &user) {
        return user->userName == userName;
    });

    if (it != users.end()) {
        return false; // User already exists
    }

    // Create a new Passenger object with all the required data
    auto newUser = make_shared<Passenger>(userName, password, user_id, email, loyalty_points);
    

    // Add the new user to the users list
    users.push_back(newUser);

    // Save users to the file
    saveUsers(users, "user.json");
    return true;

}



bool Admin::deleteUser(string userName) {
    loadUsers(users, "user.json");

    auto it = find_if(users.begin(), users.end(), [&](const shared_ptr<User>& user) {
        return user->userName == userName;
    });

    if (it != users.end()) {
        users.erase(it);
        saveUsers(users, "user.json");
        return true;
    }

    return false;
}

bool Admin::updateUser(string userName, string newPassword) {
    loadUsers(users, "user.json");

    auto it = find_if(users.begin(), users.end(), [&](shared_ptr<User>& user) {
        return user->userName == userName;
    });

    if (it != users.end()) {
        if (newPassword == (*it)->password) {
            cout << "Enter a new password" << endl;
            return false;
        }

        (*it)->password = newPassword;
        saveUsers(users, "user.json");
        return true;
    }

    cout << "User name doesn't exist" << endl;
    return false;
}

bool Admin::logUser(string userName, string password) {
    loadUsers(users, "user.json");
    auto it = find_if(users.begin(), users.end(), [&](const shared_ptr<User>& user) {
        return user->userName == userName && user->password == password;
    });

    if (it != users.end()) {
        cout << "User Logged in Successfully" << endl;
        return true;
    }

    cout << "Wrong User name or Password" << endl;
    return false;
}


/* End of Admin User Relation*/



/***************************************************  Start of Admin Flight Relation ***************************************************/



bool Admin::addFlight(string flightNumber, string origin, string destination, string depratureTime, string arrivalTime, int seats, string status) {
    loadFlights(Flights, "Flights.json");

    /* Check if flight already added */
    auto it = find_if(Flights.begin(), Flights.end(), [&](const shared_ptr<Flight>& f) {
        return f->flightNumber == flightNumber;
    });

    /* Flight is already added */
    if (it != Flights.end()) {
        return false;
    }

    // Create a shared pointer for a new Passenger object
    Flights.emplace_back(make_shared<Flight>(flightNumber, origin, destination, depratureTime, arrivalTime, seats, status));
    
    saveFlights(Flights, "Flights.json");
    return true;
}

bool Admin::updateFlight(string flightNumber, string newOrigin, string newDestination,
    string newDepartureTime, string newArrivalTime,int newSeats, string newStatus) {
    loadFlights(Flights, "Flights.json");

    auto it = find_if(Flights.begin(), Flights.end(), [&](const shared_ptr<Flight>& f) {
    return f->flightNumber == flightNumber;
    });

    if (it == Flights.end()) {
        return false; // Flight not found
    }

    (*it)->origin = newOrigin;
    (*it)->destination = newDestination;
    (*it)->depratureTime = newDepartureTime;
    (*it)->arrivalTime = newArrivalTime;
    (*it)->total_seats = newSeats;
    (*it)->status = newStatus;

    saveFlights(Flights, "Flights.json");
    return true;
}


bool Admin::deleteFlight(string flightNumber) {
    loadFlights(Flights, "Flights.json");

    auto it = find_if(Flights.begin(), Flights.end(), [&](const shared_ptr<Flight>& f) {
        return f->flightNumber == flightNumber;
    });

    if (it == Flights.end()) {
        return false; // Flight not found
    }

    Flights.erase(it);
    saveFlights(Flights, "Flights.json");
    return true;
}



/*************************************************** End of Admin Flight Relation ***************************************************/