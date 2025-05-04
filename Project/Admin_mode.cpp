#include "Admin_mode.hpp"
#include <iostream>
#include <string>

using namespace std;

void AdminMode::startAdminMode() {
    Admin admin;
    string username, password;

    cout << "--- Administrator Login ---" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (admin.Login(username, password)) {
        cout << "\nLogin Successful!" << endl;

        while (true) {
            int choice;
            cout << "\n--- Administrator Menu ---" << endl;
            cout << "1. Manage Flights" << endl;
            cout << "2. Manage Aircrafts" << endl;
            cout << "3. Manage Users" << endl;
            cout << "4. Manage Crew Assignments" << endl;
            cout << "5. Generate Reports" << endl;
            cout << "6. Logout" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    manageFlights(admin);
                    break;
                case 2:
                    manageAircrafts(admin);
                    break;
                case 3:
                    manageUsers(admin);
                    break;
                case 4:
                    manageCrewAssignments(admin);
                    break;
                case 5:
                    GenerateReports(admin);
                    return;
                case 6:
                    cout << "Logging out..." << endl;
                    cout << endl << endl;
                    return;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    } else {
        cout << "Invalid username or password. Access denied." << endl;
    }
}

/********************************************************* Manage Flights *********************************************************/
void AdminMode::manageFlights(Admin &admin) {
    while (true) {
        int choice;
        cout << "\n--- Manage Flights ---" << endl;
        cout << "1. Add New Flight" << endl;
        cout << "2. Update Existing Flight" << endl;
        cout << "3. Remove Flight" << endl;
        cout << "4. View All Flights" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addNewFlight(admin);
                break;
            case 2:
                updateFlight(admin);
                break;
            case 3:
                removeFlight(admin);
                break;
            case 4:
                viewAllFlights(admin);
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void AdminMode::addNewFlight(Admin &admin) {
    cout << endl << endl;
    displayFlights(admin);
    cout << endl << endl;
    string flightNumber, origin, destination, departureDateTime, arrivalDateTime, status;
    int totalSeats;
    double price;

    cout << "--- Add New Flight ---" << endl;
    cout << "Enter Flight Number: ";
    cin >> flightNumber;
    cin.ignore();
    cout << "Enter Origin: ";
    getline(cin, origin);
    cout << "Enter Destination: ";
    getline(cin, destination);
    cout << "Enter Departure Date and Time (YYYY-MM-DD HH:MM): ";
    getline(cin, departureDateTime);
    cout << "Enter Arrival Date and Time (YYYY-MM-DD HH:MM): ";
    getline(cin, arrivalDateTime);
    cout << "Enter Total Seats: ";
    cin >> totalSeats;
    cout << "Enter Price: ";
    cin >> price;
    cin.ignore();
    cout << "Enter Status (Scheduled/Delayed/Canceled): ";
    getline(cin, status);

    if (admin.addFlight(flightNumber, origin, destination, departureDateTime, arrivalDateTime, totalSeats, status, price)) {
        cout << "Flight added successfully!" << endl;
    } else {
        cout << "Failed to add flight. Flight number may already exist." << endl;
    }
}

void AdminMode::updateFlight(Admin &admin) {
    cout << endl << endl;
    displayFlights(admin);
    cout << endl << endl;
    string flightNumber, newOrigin, newDestination, newDepartureTime, newArrivalTime, newStatus;
    int newSeats;
    double newPrice;

    cout << "--- Update Flight ---" << endl;
    cout << "Enter Flight Number to Update: ";
    cin >> flightNumber;
    cin.ignore();
    cout << "Enter New Origin: ";
    getline(cin, newOrigin);
    cout << "Enter New Destination: ";
    getline(cin, newDestination);
    cout << "Enter New Departure Date and Time (YYYY-MM-DD HH:MM): ";
    getline(cin, newDepartureTime);
    cout << "Enter New Arrival Date and Time (YYYY-MM-DD HH:MM): ";
    getline(cin, newArrivalTime);
    cout << "Enter New Total Seats: ";
    cin >> newSeats;
    cout << "Enter New Price: ";
    cin >> newPrice;
    cin.ignore();
    cout << "Enter New Status (Scheduled/Delayed/Canceled): ";
    getline(cin, newStatus);

    if (admin.updateFlight(flightNumber, newOrigin, newDestination, newDepartureTime, newArrivalTime, newSeats, newStatus, newPrice)) {
        cout << "Flight updated successfully!" << endl;
    } else {
        cout << "Failed to update flight. Flight number may not exist." << endl;
    }
}

void AdminMode::removeFlight(Admin &admin) {
    cout << endl << endl;
    displayFlights(admin);
    cout << endl << endl;
    string flightNumber;
    cout << "--- Remove Flight ---" << endl;
    cout << "Enter Flight Number to Remove: ";
    cin >> flightNumber;

    if (admin.deleteFlight(flightNumber)) {
        cout << "Flight removed successfully!" << endl;
    } else {
        cout << "Failed to remove flight. Flight number may not exist." << endl;
    }
}

void AdminMode::viewAllFlights(Admin &admin) {
    cout << endl << endl;
    cout << "--- View All Flights ---" << endl;
    loadData<Flight>(admin.Flights, "Flights.json");
    for (const auto &flight : admin.Flights) {
        cout << "Flight Number: " << flight->flightNumber << endl;
        cout << "Origin: " << flight->origin << endl;
        cout << "Destination: " << flight->destination << endl;
        cout << "Departure: " << flight->depratureTime << endl;
        cout << "Arrival: " << flight->arrivalTime << endl;
        cout << "Seats: " << flight->total_seats << endl;
        cout << "Price: $" << flight->price << endl;
        cout << "Status: " << flight->status << endl;
        cout << "------------------------" << endl;
    }
}

/********************************************************* Manage Aircrafts *********************************************************/
void AdminMode::manageAircrafts(Admin &admin) {
    while (true) {
        int choice;
        cout << "\n--- Manage Aircrafts ---" << endl;
        cout << "1. Add New Aircraft" << endl;
        cout << "2. Assign Aircraft to Flight" << endl;
        cout << "3. Add Maintenance" << endl;
        cout  << "4. View All Aircrafts" << endl;
        cout << "5. View Maintenance Schedules" << endl;
        cout << "6. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addAircraft(admin);
                break;
            case 2:
                assignAircraft(admin);
                break;
            case 3:
                cout << endl << endl;
                addMaintenance(admin);
                cout << endl << endl;
                return;
            case 4:
                cout << endl << endl;
                displayAircrafts(admin);
                cout << endl << endl;
                break;
            case 5:
                cout << endl << endl;
                displayMaintenanceSchedules(admin);
                cout << endl << endl;
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void AdminMode::addAircraft(Admin &admin) {
    string model, id;
    int capacity;
    double maxSpeed;

    cout << "--- Add New Aircraft ---" << endl;
    cout << "Enter Aircraft Model: ";
    cin >> model;
    cout << "Enter Aircraft ID: ";
    cin >> id;
    cout << "Enter Capacity: ";
    cin >> capacity;
    cout << "Enter Max Speed: ";
    cin >> maxSpeed;

    if (admin.addAircraft(model, id, capacity, maxSpeed)) {
        cout << "Aircraft added successfully!" << endl;
    } else {
        cout << "Failed to add aircraft. Aircraft ID may already exist." << endl;
    }
}

void AdminMode::assignAircraft(Admin &admin) {
    cout << endl << endl;
    displayAircrafts(admin);
    cout << endl << endl;
    displayFlights(admin);
    cout << endl << endl;
    string aircraftID, flightID;
    cout << endl << endl;
    displayAircraftAssignments(admin);
    cout << endl << endl;

    cout << "--- Assign Aircraft to Flight ---" << endl;
    cout << "Enter Aircraft ID: ";
    cin >> aircraftID;
    cout << "Enter Flight ID: ";
    cin >> flightID;

    if (admin.assignAircraftToFlight(aircraftID, flightID)) {
        cout << "Aircraft assigned successfully!" << endl;
    } else {
        cout << "Failed to assign aircraft. Aircraft or flight ID may not exist." << endl;
    }
}

/********************************************************* Manage Users *********************************************************/
void AdminMode::manageUsers(Admin &admin) {
    while (true) {
        int choice;
        cout << "\n--- Manage Users ---" << endl;
        cout << "1. Add New User" << endl;
        cout << "2. Update User" << endl;
        cout << "3. Delete User" << endl;
        cout << "4. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addUser(admin);
                break;
            case 2:
                updateUser(admin);
                break;
            case 3:
                deleteUser(admin);
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void AdminMode::addUser(Admin &admin) {
    cout << endl << endl;
    displayUsers(admin);
    string userName, password, email;
    int user_id, loyalty_points;

    cout << "--- Add New User ---" << endl;
    cout << "Enter Username: ";
    cin.ignore(); // Clear the leftover newline from previous input
    getline(cin, userName); // Allow spaces in username

    cout << "Enter Password: ";
    cin >> password;

    cout << "Enter User ID: ";
    cin >> user_id;

    cout << "Enter Email: ";
    cin >> email;

    cout << "Enter Loyalty Points: ";
    cin >> loyalty_points;

    if (admin.addUser(userName, password, user_id, email, loyalty_points)) {
        cout << "User added successfully!" << endl;
    } else {
        cout << "Failed to add user" << endl;
    }
}

void AdminMode::updateUser(Admin &admin) {
    cout << endl << endl;
    displayUsers(admin);
    string userName, newPassword;
    cout << "--- Update User ---" << endl;
    cout << "Enter Username to Update: ";
    cin.ignore(); // Clear input buffer
    getline(cin, userName); // Read full line, including spaces
    cout << "Enter New Password: ";
    cin >> newPassword;

    if (admin.updateUser(userName, newPassword)) {
        cout << "User updated successfully!" << endl;
    } else {
        cout << "Failed to update user. Username may not exist." << endl;
    }
}

void AdminMode::deleteUser(Admin &admin) {
    displayUsers(admin);
    string userName;

    cout << "--- Delete User ---" << endl;
    cout << "Enter Username to Delete: ";
    cin >> userName;

    if (admin.deleteUser(userName)) {
        cout << "User deleted successfully!" << endl;
    } else {
        cout << "Failed to delete user. Username may not exist." << endl;
    }
}

/********************************************************* Manage Crew Assignments *********************************************************/
void AdminMode::manageCrewAssignments(Admin &admin) {
    cout << endl << endl;
    displayPilots(admin);
    cout << endl << endl;
    displayFlightAttendants(admin);
    cout << endl << endl;
    displayFlights(admin);
    cout << endl << endl;
    displayCrewAssignments(admin);
    cout << endl << endl;
    string captainID, attendantID, flightID;

    cout << "--- Assign Crew to Flight ---" << endl;
    cout << "Enter Captain ID: ";
    cin >> captainID;
    cout << "Enter Attendant ID: ";
    cin >> attendantID;
    cout << "Enter Flight ID: ";
    cin >> flightID;

    if (admin.assignCrew(captainID, attendantID, flightID)) {
        cout << "Crew assigned successfully!" << endl;
    } else {
        cout << "Failed to assign crew. IDs may not exist." << endl;
    }
}

/********************************************************* Display Users *********************************************************/
void AdminMode::displayUsers(Admin &admin) {
    cout << "--- Display All Users ---" << endl;
    loadUsers(admin.users, "user.json");
    for (const auto &user : admin.users) {
        auto passenger = dynamic_pointer_cast<Passenger>(user);
        if (passenger) {
            cout << "Username: " << passenger->getUserName() << endl;
            cout << "User ID: " << passenger->getUserId() << endl;
            cout << "Email: " << passenger->getEmail() << endl;
            cout << "Loyalty Points: " << passenger->getLoyaltyPoints() << endl;
            cout << "Balance: $" << passenger->getBalance() << endl;
            cout << "------------------------" << endl;
        }
    }
}

/********************************************************* Display Flights *********************************************************/
void AdminMode::displayFlights(Admin &admin) {
    cout << "--- Display All Flights ---" << endl;
    loadData<Flight>(admin.Flights, "Flights.json");
    for (const auto &flight : admin.Flights) {
        cout << "Flight Number: " << flight->flightNumber << endl;
        cout << "Origin: " << flight->origin << endl;
        cout << "Destination: " << flight->destination << endl;
        cout << "Departure: " << flight->depratureTime << endl;
        cout << "Arrival: " << flight->arrivalTime << endl;
        cout << "Seats: " << flight->total_seats << endl;
        cout << "Price: $" << flight->price << endl;
        cout << "Status: " << flight->status << endl;
        cout << "------------------------" << endl;
    }
}

/********************************************************* Display Pilots *********************************************************/
void AdminMode::displayPilots(Admin &admin) {
    cout << "--- Display All Pilots ---" << endl;
    loadData<Pilot>(admin.pilots, "pilots.json");
    for (const auto &pilot : admin.pilots) {
        cout << "Pilot Name: " << pilot->pilotName << endl;
        cout << "Pilot ID: " << pilot->pilotID << endl;
        cout << "------------------------" << endl;
    }
}

/********************************************************* Display Flight Attendants *********************************************************/
void AdminMode::displayFlightAttendants(Admin &admin) {
    cout << "--- Display All Flight Attendants ---" << endl;
    loadData<FlightAttendant>(admin.flightAttendants, "FlightAttendants.json");
    for (const auto &attendant : admin.flightAttendants) {
        cout << "Attendant Name: " << attendant->getAttendantName() << endl;
        cout << "Attendant ID: " << attendant->getAttendantID() << endl;
        cout << "------------------------" << endl;
    }
}

/********************************************************* Display Aircrafts *********************************************************/
void AdminMode::displayAircrafts(Admin &admin) {
    cout << "--- Display All Aircrafts ---" << endl;
    loadData<Aircraft>(admin.aircrafts, "Aircrafts.json");
    for (const auto &aircraft : admin.aircrafts) {
        cout << "Aircraft Model: " << aircraft->getModel() << endl;
        cout << "Aircraft ID: " << aircraft->getId() << endl;
        cout << "Capacity: " << aircraft->getCapacity() << endl;
        cout << "Max Speed: " << aircraft->getMaxSpeed() << endl;
        cout << "------------------------" << endl;
    }
}

/**************************** Display Crew Assignment ************************/
void AdminMode::displayCrewAssignments(Admin &admin) {
    cout << "--- Display All Crew Assignments ---" << endl;

    // Load the crew assignments from the JSON file
    json allAssignments;
    ifstream inFile("crewAssignment.json");
    if (inFile.is_open()) {
        inFile >> allAssignments;
        inFile.close();
    } else {
        cout << "No crew assignments found. The file 'crewAssignment.json' does not exist or is empty." << endl;
        return;
    }

    // Display each crew assignment
    for (const auto& assignment : allAssignments) {
        cout << "Flight Number: " << assignment["flightNumber"] << endl;
        cout << "Origin: " << assignment["origin"] << endl;
        cout << "Destination: " << assignment["destination"] << endl;
        cout << "Captain Name: " << assignment["pilotName"] << endl;
        cout << "Captain ID: " << assignment["pilotID"] << endl;
        cout << "Attendant Name: " << assignment["attendantName"] << endl;
        cout << "Attendant ID: " << assignment["attendantID"] << endl;
        cout << "------------------------" << endl;
    }
}


/**************************** Display Aircraft Assignments ************************/
void AdminMode::displayAircraftAssignments(Admin &admin) {
    cout << "--- Display All Aircraft Assignments ---" << endl;

    // Load the aircraft assignments from the JSON file
    json allAssignments;
    ifstream inFile("AircraftAssignment.json");
    if (inFile.is_open()) {
        inFile >> allAssignments;
        inFile.close();
    } else {
        cout << "No aircraft assignments found. The file 'AircraftAssignment.json' does not exist or is empty." << endl;
        return;
    }

    // Display each aircraft assignment
    for (const auto& assignment : allAssignments) {
        cout << "Flight Number: " << assignment["flightNumber"] << endl;
        cout << "Aircraft Model: " << assignment["aircraftModel"] << endl;
        cout << "Aircraft ID: " << assignment["aircraftID"] << endl;
        cout << "------------------------" << endl;
    }
}

/**************************** Display Maintenance Schedules ************************/
void AdminMode::displayMaintenanceSchedules(Admin &admin) {
    // use loadData<Maintenance> to load the maintenance schedules
    cout << "--- Display All Maintenance Schedules ---" << endl;
    loadData<Maintenance>(admin.maintenances, "Maintenance.json");
    for (const auto &maintenance : admin.maintenances) {
        cout << "Aircraft ID: " << maintenance->getAircraftId() << endl;
        cout << "Maintenance Type: " << maintenance->getMaintenanceType() << endl;
        cout << "Start Date: " << maintenance->getStartDate() << endl;
        cout << "End Date: " << maintenance->getEndDate() << endl;
        cout << "Description: " << maintenance->getDescription() << endl;
        cout << "Estimated Cost: $" << maintenance->getEstimatedCost() << endl;
        cout << "------------------------" << endl;
    }
}

/**************************** Add Maintenance ************************/
void AdminMode::addMaintenance(Admin &admin) {
    string aircraftID, maintenanceType, startDate, endDate, description;
    double estimatedCost;

    cout << endl << endl;
    displayAircrafts(admin);
    cout << endl << endl;
    displayMaintenanceSchedules(admin);
    cout << endl << endl;

    cout << "--- Add Maintenance ---" << endl;
    cout << "Enter Aircraft ID: ";
    cin >> aircraftID;
    cout << "Enter Maintenance Type: Motor/Avionics/Other: ";
    cin >> maintenanceType;
    cout << "Enter Start Date (YYYY-MM-DD): ";
    cin >> startDate;
    cout << "Enter End Date (YYYY-MM-DD): ";
    cin >> endDate;
    cout << "Enter Description: ";
    cin.ignore(); // Clear the newline character from the input buffer
    getline(cin, description); // Allow spaces in description
    cout << "Enter Estimated Cost: ";
    cin >> estimatedCost;

    if (admin.addMaintenance(aircraftID, maintenanceType, startDate, endDate, description, estimatedCost)) {
        cout << "Maintenance added successfully!" << endl;
    } else {
        cout << "Failed to add maintenance. Aircraft ID may not exist." << endl;
    }
}




/********************************************************* Generate Reports *********************************************************/
void AdminMode::GenerateReports(Admin &admin) {
    while (true) {
        int choice;
        cout << "\n--- Generate Reports ---" << endl;
        cout << "1. Maintenance Report" << endl;
        cout << "2. Flight Report" << endl;
        cout << "3. User Report" << endl;
        cout << "4. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << endl << endl;
                displayMaintenanceSchedules(admin);
                break;
            case 2:
                cout << endl << endl;
                displayFlights(admin);
                break;
            case 3:
                cout << endl << endl;
                displayUsers(admin);
                break;
            case 4:
                cout << endl << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    
}

