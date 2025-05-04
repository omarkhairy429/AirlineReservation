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



bool Admin::addFlight(string flightNumber, string origin, string destination, string depratureTime, string arrivalTime, int seats, string status, double price) {
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
    Flights.emplace_back(make_shared<Flight>(flightNumber, origin, destination, depratureTime, arrivalTime, seats, status, price));
    
    saveFlights(Flights, "Flights.json");
    return true;
}

bool Admin::updateFlight(string flightNumber, string newOrigin, string newDestination,
    string newDepartureTime, string newArrivalTime,int newSeats, string newStatus, double newPrice) {
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
    (*it)->price = newPrice;

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



/*************************************************** Pilot, Flight Attendants ***************************************************/
bool Admin::addPilot(string pilotName, string pilotID) {
    loadPilots(pilots, "pilots.json");
    auto it = find_if(pilots.begin(), pilots.end(), [&](const std::shared_ptr<Pilot>& p) {
        return p->pilotID == pilotID;
    });

    if (it != pilots.end()) {
        cout << "This Pilot ID already exists" << endl;
        return false;
    }

    Pilot newPilot;
    newPilot.pilotName = pilotName;
    newPilot.pilotID = pilotID;
    pilots.emplace_back(make_shared<Pilot>(newPilot));
    savePilots(pilots, "pilots.json");
    return true;
}

bool Admin::addFlightAttendant(string name, string id) {
    loadFlightAttendants(flightAttendants, "FlightAttendants.json");

    auto it = find_if(flightAttendants.begin(), flightAttendants.end(), [&](const std::shared_ptr<FlightAttendant>& f) {
        return f->attendantID == id;
    });

    if (it != flightAttendants.end()) {
        cout << "This Flight Attendant ID already exists" << endl;
        return false;
    }

    FlightAttendant newAttendant;
    newAttendant.attendantName = name;
    newAttendant.attendantID = id;
    flightAttendants.emplace_back(make_shared<FlightAttendant>(newAttendant));
    saveFlightAttendants(flightAttendants, "FlightAttendants.json");
    return true;
}

/*************************************************** Assigning crew to the flight ***************************************************/
bool Admin::assignCrew(string captainID, string attendantID, string flightID) {
    loadPilots(pilots, "pilots.json");
    loadFlightAttendants(flightAttendants, "FlightAttendants.json");
    loadFlights(Flights, "Flights.json");

    // Find pilot
    auto pilotIt = find_if(pilots.begin(), pilots.end(), [&](const shared_ptr<Pilot>& p) {
        return p->pilotID == captainID;
    });

    // Find flight attendant
    auto attendantIt = find_if(flightAttendants.begin(), flightAttendants.end(), [&](const shared_ptr<FlightAttendant>& a) {
        return a->attendantID == attendantID;
    });

    // Find flight
    auto flightIt = find_if(Flights.begin(), Flights.end(), [&](const shared_ptr<Flight>& f) {
        return f->flightNumber == flightID;
    });

    // Validate
    if (pilotIt == pilots.end() || attendantIt == flightAttendants.end() || flightIt == Flights.end()) {
        cout << "Invalid pilot, flight attendant, or flight ID." << endl;
        return false;
    }

    // Build JSON for the new crew assignment
    json newCrewAssignment = {
        {"pilotName", (*pilotIt)->pilotName},
        {"pilotID", (*pilotIt)->pilotID},
        {"attendantName", (*attendantIt)->attendantName},
        {"attendantID", (*attendantIt)->attendantID},
        {"flightNumber", (*flightIt)->flightNumber},
        {"origin", (*flightIt)->origin},
        {"destination", (*flightIt)->destination}
    };

    // Load or initialize crewAssignment.json
    json allAssignments;
    ifstream inFile("crewAssignment.json");
    if (inFile.is_open()) {
        inFile >> allAssignments;
        inFile.close();
    }

    // Check if a crew is already assigned to the flight
    auto existingAssignmentIt = find_if(allAssignments.begin(), allAssignments.end(), [&](const json& assignment) {
        return assignment["flightNumber"] == flightID;
    });

    if (existingAssignmentIt != allAssignments.end()) {
        // Update the existing assignment
        *existingAssignmentIt = newCrewAssignment;
        cout << "Crew assignment updated for flight " << flightID << "." << endl;
    } else {
        // Add the new assignment
        allAssignments.push_back(newCrewAssignment);
        cout << "Crew assigned successfully to flight " << flightID << "." << endl;
    }

    // Save the updated assignments back to the file
    ofstream outFile("crewAssignment.json");
    outFile << setw(4) << allAssignments << endl;
    outFile.close();

    return true;
}

/*************************************************** Add Aircrafts ***************************************************/

bool Admin:: addAircraft(string model, string id, int capacity, double maxSpeed) {
    loadAircraft(aircrafts, "Aircrafts.json");
    /* ID should be unique */
    auto it = find_if(aircrafts.begin(), aircrafts.end(), [&](const std::shared_ptr<Aircraft>& aircraft) {
        return aircraft->getId() == id;
    });
    
    if(it != aircrafts.end()) {
        cout << "This Aircraft already exists" << endl;
        return false;
    }

    aircrafts.emplace_back(make_shared<Aircraft>(model, id, capacity, maxSpeed));
    saveAircraft(aircrafts, "Aircrafts.json");
    return true;
}


