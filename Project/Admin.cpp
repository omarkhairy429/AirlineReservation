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
bool Admin::addUser(string userName, string password) {
    loadUsers();

    /* Check if username is not taken */
    auto it = find_if(users.begin(), users.end(), [&](const shared_ptr<User>& user) {
        return user->userName == userName;
    });

    /* Name is already taken */
    if (it != users.end()) {
        return false;
    }

    // Create a shared pointer for a new Passenger object
    users.push_back(make_shared<Passenger>(userName, password));
    saveUsers();
    return true;
}

void Admin::saveUsers() {
    json j;
    for (const auto& user : users) {
        j.emplace_back(*user); 
    }
    
    ofstream file("user.json");
    file << j.dump(4);
}

void Admin::loadUsers() {
    ifstream file("user.json");

    if (!file) {
        cerr << "Error: Unable to open user.json file." << endl;
        return;
    }

    try {
        json j;
        file >> j;

        if (j.is_array()) {
            users.clear();
            for (const auto& item : j) {
                users.push_back(make_shared<Passenger>(item.get<Passenger>()));
            }
        } else {
            cerr << "Error: JSON format is incorrect. Expected an array." << endl;
        }
    } catch (const json::exception& e) {
        cerr << "Error: Failed to parse user.json file. Exception: " << e.what() << endl;
    }
}


bool Admin::deleteUser(string userName) {
    loadUsers();

    auto it = find_if(users.begin(), users.end(), [&](const shared_ptr<User>& user) {
        return user->userName == userName;
    });

    if (it != users.end()) {
        users.erase(it);
        saveUsers();
        return true;
    }

    return false;
}

bool Admin::updateUser(string userName, string newPassword) {
    loadUsers();

    auto it = find_if(users.begin(), users.end(), [&](shared_ptr<User>& user) {
        return user->userName == userName;
    });

    if (it != users.end()) {
        if (newPassword == (*it)->password) {
            cout << "Enter a new password" << endl;
            return false;
        }

        (*it)->password = newPassword;
        saveUsers();
        return true;
    }

    cout << "User name doesn't exist" << endl;
    return false;
}

bool Admin::logUser(string userName, string password) {
    loadUsers();
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

void Admin::loadFlights() {
    ifstream file("Flights.json");
    if (!file) {
        ofstream createFile("Flights.json");  // Create the file
        return; 
    }

    try {
        json j;
        file >> j;

        if (j.is_array()) {
            Flights.clear();
            for (const auto& item : j) {
                Flights.emplace_back(make_shared<Flight>(item.get<Flight>()));
            }
        } else {
            cerr << "Error: JSON format is incorrect. Expected an array." << endl;
        }
    } catch (const json::exception& e) {
        cerr << "Error: Failed to parse user.json file. Exception: " << e.what() << endl;
    }
}

void Admin::saveFlights() {
    json j;
    for (const auto& flight : Flights) {
        j.emplace_back(*flight); 
    }
    
    ofstream file("Flights.json");
    file << j.dump(4);
}


bool Admin::addFlight(string flightNumber, string origin, string destination, string depratureTime, string arrivalTime, string status) {
    loadFlights();

    /* Check if flight already added */
    auto it = find_if(Flights.begin(), Flights.end(), [&](const shared_ptr<Flight>& f) {
        return f->flightNumber == flightNumber;
    });

    /* Flight is already added */
    if (it != Flights.end()) {
        return false;
    }

    // Create a shared pointer for a new Passenger object
    Flights.emplace_back(make_shared<Flight>(flightNumber, origin, destination, depratureTime, arrivalTime, status));
    saveFlights();
    return true;
}

bool Admin::updateFlight(string flightNumber, string newOrigin, string newDestination,
    string newDepartureTime, string newArrivalTime, string newStatus) {
    loadFlights();

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
    (*it)->status = newStatus;

    saveFlights();
    return true;
}


bool Admin::deleteFlight(string flightNumber) {
    loadFlights();

    auto it = find_if(Flights.begin(), Flights.end(), [&](const shared_ptr<Flight>& f) {
        return f->flightNumber == flightNumber;
    });

    if (it == Flights.end()) {
        return false; // Flight not found
    }

    Flights.erase(it);
    saveFlights();
    return true;
}



/*************************************************** End of Admin Flight Relation ***************************************************/