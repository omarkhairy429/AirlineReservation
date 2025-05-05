#include "Admin.hpp"
#include <fstream>
#include <algorithm>


using namespace std;
using json = nlohmann::json;

/********************************************* Password Encryption *********************************************/
string Admin::encryptPassword(const string& password, const string& key) {
    string encrypted = password;
    for (size_t i = 0; i < password.size(); ++i) {
        encrypted[i] ^= key[i % key.size()];
    }
    return encrypted;
}

string Admin::decryptPassword(const string& encryptedPassword, const string& key) {
    // XOR decryption is the same as encryption
    return encryptPassword(encryptedPassword, key);
}



/* Start of Admin User relation */

// Admin logs in
bool Admin::Login(string userName, string password) {
    return userName == "admin" && password == "12345";
}

// Admin logs a user
bool Admin::addUser(string userName, string password, int user_id, string email, int loyalty_points) {
    loadUsers(users, "user.json");

    // Check if the username or user ID already exists
    auto it = std::find_if(users.begin(), users.end(), [&](const std::shared_ptr<User>& user) {
        auto passenger = std::dynamic_pointer_cast<Passenger>(user);
        if (user->userName == userName) {
            cout << "Username already exists.\n";
            return true;
        }
        if (passenger && passenger->getUserId() == user_id) {
            cout << "User ID already exists.\n";
            return true;
        }
        return false;
    });

    if (it != users.end()) {
        return false;
    }

    // Encrypt the password before saving
    string encryptedPassword = encryptPassword(password);

    auto newUser = std::make_shared<Passenger>(userName, encryptedPassword, user_id, email, loyalty_points);
    newUser->setBalance(0);
    users.push_back(newUser);
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
        return user->userName == userName;
    });

    if (it != users.end()) {
        // Decrypt the stored password
        string decryptedPassword = decryptPassword((*it)->password);

        if (decryptedPassword == password) {
            cout << "User Logged in Successfully" << endl;
            return true;
        } else {
            cout << "Wrong Password" << endl;
            return false;
        }
    }

    cout << "Wrong User name or Password" << endl;
    return false;
}


/* End of Admin User Relation*/



/***************************************************  Start of Admin Flight Relation ***************************************************/



bool Admin::addFlight(string flightNumber, string origin, string destination, string depratureTime, string arrivalTime, int seats, string status, double price) {
    loadData<Flight>(Flights, "Flights.json");

    /* Check if flight already added */
    auto it = find_if(Flights.begin(), Flights.end(), [&](const shared_ptr<Flight>& f) {
        return f->getFlightNumber() == flightNumber;
    });

    /* Flight is already added */
    if (it != Flights.end()) {
        return false;
    }

    // Create a shared pointer for a new Passenger object
    Flights.emplace_back(make_shared<Flight>(flightNumber, origin, destination, depratureTime, arrivalTime, seats, status, price));
    
    saveData<Flight>(Flights, "Flights.json");
    return true;
}

bool Admin::updateFlight(string flightNumber, string newOrigin, string newDestination,
    string newDepartureTime, string newArrivalTime,int newSeats, string newStatus, double newPrice) {
    loadData<Flight>(Flights, "Flights.json");

    auto it = find_if(Flights.begin(), Flights.end(), [&](const shared_ptr<Flight>& f) {
    return f->getFlightNumber() == flightNumber;
    });

    if (it == Flights.end()) {
        return false; // Flight not found
    }

    (*it)->setOrigin(newOrigin);
    (*it)->setDestination(newDestination);
    (*it)->setDepratureTime(newDepartureTime);
    (*it)->setArrivalTime(newArrivalTime);
    (*it)->setTotalSeats(newSeats);
    (*it)->setStatus(newStatus);
    (*it)->setPrice(newPrice);


    saveData<Flight>(Flights, "Flights.json");
    return true;
}


bool Admin::deleteFlight(string flightNumber) {
    // Load flights and reservations
    loadData<Flight>(Flights, "Flights.json");
    loadData<Reservation>(reservations, "Reservations.json");
    loadUsers(users, "user.json");

    // Find the flight
    auto flightIt = find_if(Flights.begin(), Flights.end(), [&](const shared_ptr<Flight>& f) {
        return f->getFlightNumber() == flightNumber;
    });

    if (flightIt == Flights.end()) {
        return false; // Flight not found
    }

    // Delete all reservations attached to this flight and refund money
    auto reservationIt = reservations.begin();
    while (reservationIt != reservations.end()) {
        if ((*reservationIt)->getFlightNumber() == flightNumber) {
            // Refund money to the user
            auto userIt = find_if(users.begin(), users.end(), [&](const shared_ptr<User>& user) {
                auto it = dynamic_pointer_cast<Passenger>(user);
                return it->getUserId() == (*reservationIt)->getPassengerID();
            });

            if (userIt != users.end()) {
                auto passenger = dynamic_pointer_cast<Passenger>(*userIt);
                if (passenger) {
                    passenger->setBalance(passenger->getBalance() + (*flightIt)->getPrice());
                }
            }

            // Erase the reservation
            reservationIt = reservations.erase(reservationIt);
        } else {
            ++reservationIt;
        }
    }

    // Save updated reservations and users
    saveData<Reservation>(reservations, "Reservations.json");
    saveUsers(users, "user.json");

    // Delete the flight
    Flights.erase(flightIt);
    saveData<Flight>(Flights, "Flights.json");

    return true;
}



/*************************************************** End of Admin Flight Relation ***************************************************/



/*************************************************** Pilot, Flight Attendants ***************************************************/
bool Admin::addPilot(string pilotName, string pilotID) {
    loadData<Pilot>(pilots, "pilots.json");
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
    saveData<Pilot>(pilots, "pilots.json");
    return true;
}

bool Admin::addFlightAttendant(string name, string id) {
    loadData<FlightAttendant>(flightAttendants, "FlightAttendants.json");

    auto it = find_if(flightAttendants.begin(), flightAttendants.end(), [&](const std::shared_ptr<FlightAttendant>& f) {
        return f->getAttendantID() == id;
    });

    if (it != flightAttendants.end()) {
        cout << "This Flight Attendant ID already exists" << endl;
        return false;
    }

    FlightAttendant newAttendant;
    newAttendant.setAttendantName(name);
    newAttendant.setAttendantID(id);
    flightAttendants.emplace_back(make_shared<FlightAttendant>(newAttendant));
    saveData<FlightAttendant>(flightAttendants, "FlightAttendants.json");
    return true;
}

/*************************************************** Assigning crew to the flight ***************************************************/
bool Admin::assignCrew(string captainID, string attendantID, string flightID) {
    loadData<Pilot>(pilots, "pilots.json");
    loadData<FlightAttendant>(flightAttendants, "FlightAttendants.json");
    loadData<Flight>(Flights, "Flights.json");

    // Find pilot
    auto pilotIt = find_if(pilots.begin(), pilots.end(), [&](const shared_ptr<Pilot>& p) {
        return p->pilotID == captainID;
    });

    // Find flight attendant
    auto attendantIt = find_if(flightAttendants.begin(), flightAttendants.end(), [&](const shared_ptr<FlightAttendant>& a) {
        return a->getAttendantID() == attendantID;
    });

    // Find flight
    auto flightIt = find_if(Flights.begin(), Flights.end(), [&](const shared_ptr<Flight>& f) {
        return f->getFlightNumber() == flightID;
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
        {"attendantName", (*attendantIt)->getAttendantName()},
        {"attendantID", (*attendantIt)->getAttendantID()},
        {"flightNumber", (*flightIt)->getFlightNumber()},
        {"origin", (*flightIt)->getOrigin()},
        {"destination", (*flightIt)->getDestination()}
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
    loadData<Aircraft>(aircrafts, "Aircrafts.json");
    /* ID should be unique */
    auto it = find_if(aircrafts.begin(), aircrafts.end(), [&](const std::shared_ptr<Aircraft>& aircraft) {
        return aircraft->getId() == id;
    });
    
    if(it != aircrafts.end()) {
        cout << "This Aircraft already exists" << endl;
        return false;
    }

    aircrafts.emplace_back(make_shared<Aircraft>(model, id, capacity, maxSpeed));
    saveData<Aircraft>(aircrafts, "Aircrafts.json");
    return true;
}

/*************************************************** Assign  Aircrafts ***************************************************/

bool Admin::assignAircraftToFlight(string aircraftID, string flightID) {
    // Load existing aircrafts and flights
    loadData<Aircraft>(aircrafts, "Aircrafts.json");
    loadData<Flight>(Flights, "Flights.json");

    // Find aircraft
    auto aircraftIt = find_if(aircrafts.begin(), aircrafts.end(), [&](const shared_ptr<Aircraft>& a) {
        return a->getId() == aircraftID;
    });

    // Find flight
    auto flightIt = find_if(Flights.begin(), Flights.end(), [&](const shared_ptr<Flight>& f) {
        return f->getFlightNumber() == flightID;
    });

    // Validate
    if (aircraftIt == aircrafts.end() || flightIt == Flights.end()) {
        cout << "Invalid aircraft or flight ID." << endl;
        return false;
    }

    // Build JSON for the assignment
    json newAssignment = {
        {"aircraftID", (*aircraftIt)->getId()},
        {"aircraftModel", (*aircraftIt)->getModel()},
        {"flightNumber", (*flightIt)->getFlightNumber()},
        {"origin", (*flightIt)->getOrigin()},
        {"destination", (*flightIt)->getDestination()}
    };

    // Load or initialize AircraftAssignment.json
    json allAssignments;
    ifstream inFile("AircraftAssignment.json");
    if (inFile.is_open()) {
        inFile >> allAssignments;
        inFile.close();
    }

    // Check if assignment already exists
    auto existingAssignmentIt = find_if(allAssignments.begin(), allAssignments.end(), [&](const json& assignment) {
        return assignment["flightNumber"] == flightID;
    });

    if (existingAssignmentIt != allAssignments.end()) {
        *existingAssignmentIt = newAssignment;
        cout << "Aircraft assignment updated for flight " << flightID << "." << endl;
    } else {
        allAssignments.push_back(newAssignment);
        cout << "Aircraft assigned successfully to flight " << flightID << "." << endl;
    }

    // Save back to file
    ofstream outFile("AircraftAssignment.json");
    outFile << setw(4) << allAssignments << endl;
    outFile.close();

    return true;
}

/*************************************************** Add Maintenance ***************************************************/
bool Admin::addMaintenance(string aircraftID, string maintenanceType, string startDate, string endDate, string description, double estimatedCost) {
    loadData<Maintenance>(maintenances, "Maintenance.json");

    // Check if the aircraft ID already exists in the maintenance records
    auto it = find_if(maintenances.begin(), maintenances.end(), [&](const shared_ptr<Maintenance>& m) {
        return m->getAircraftId() == aircraftID;
    });

    if (it != maintenances.end()) {
        cout << "This Aircraft ID already exists in the maintenance records." << endl;
        return false;
    }

    // Create a new Maintenance object and add it to the vector
    auto newMaintenance = make_shared<Maintenance>(aircraftID, maintenanceType, startDate, endDate, description, estimatedCost);
    maintenances.push_back(newMaintenance);
    saveData<Maintenance>(maintenances, "Maintenance.json");
    return true;
}

