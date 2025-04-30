#include "Admin_mode.hpp"
#include <iostream>
#include <string>

using namespace std;

void AdminMode::startAdminMode() {
    Admin admin1;
    string username, password;
    cout << "--- Administrator Login ---" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (admin1.Login(username, password)) {
        int choice;
        cout << endl << "Login Successful" << endl << endl;
        cout << "--- Administrator Menu ---" << endl;
        cout << "1. Manage Flights" << endl;
        cout << "2. Manage Aircraft" << endl;
        cout << "3. Manage Users" << endl;
        cout << "4. Generate Reports" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:  // Manage Flights
                manageFlights(admin1);
                break;
            case 2:  // Manage Aircraft
                cout << "Managing Aircraft..." << endl;
                break;
            case 3:  // Manage Users
                manageUsers(admin1);
                break;
            case 4:  // Generate Reports
                cout << "Generating Reports..." << endl;
                break;
            case 5:  // Logout
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
                break;
        }
    }
}

/********************************************************* Start of Managing Flights *********************************************************/
void AdminMode::manageFlights(Admin &admin) {
    int choice;
    // Display the Manage Flights menu
    cout << endl;
    cout << "--- Manage Flights ---" << endl;
    cout << "1. Add New Flight" << endl;
    cout << "2. Update Existing Flight" << endl;
    cout << "3. Remove Flight" << endl;
    cout << "4. View All Flights" << endl;
    cout << "5. Back to Main Menu" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch(choice) {
        case 1:  // Add New Flight
            addNewFlight(admin);
            break;
        case 2:  // Update Existing Flight
            cout << "Updating an existing flight..." << endl;
            break;
        case 3:  // Remove Flight
            cout << "Removing a flight..." << endl;
            break;
        case 4:  // View All Flights
            cout << "Viewing all flights..." << endl;
            break;
        case 5:  // Back to Main Menu
            cout << "Going back to the main menu..." << endl;
            break;
        default:
            cout << "Invalid choice. Please select a valid option." << endl;
            break;
    }
}

void AdminMode::addNewFlight(Admin &admin) {
    string flightNumber, origin, destination, departureDateTime, arrivalDateTime, aircraftType, status;
    int totalSeats;

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

    cout << "Enter Aircraft Type: ";
    getline(cin, aircraftType);

    cout << "Enter Total Seats: ";
    cin >> totalSeats;

    cin.ignore();

    cout << "Enter Status (Scheduled/Delayed/Canceled): ";
    getline(cin, status);

    admin.addFlight(flightNumber, origin, destination, departureDateTime, arrivalDateTime, totalSeats ,status);
}

/************************************************************************  End of Managing Flights ********************************************************/







/************************************************************************ Start of Managing Users ************************************************************************/

void AdminMode::manageUsers(Admin& admin) {
    int choice;
    cout << "Manage User Menu" << endl;
    cout << "1: Add New User" << endl;
    cout << "2: Update User" << endl;
    cout << "3: Delete User" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    string userName, password, newPassword, email;
    int loyalty_points, user_id;

    switch (choice) {
        case 1:
            cout << "Enter userName: ";
            getline(cin, userName);
            cout << "Enter password: ";
            cin >> password;
            cin.ignore();
            cout << "Enter user ID: ";
            cin >>user_id;
            cin.ignore();
            cout << "Enter email: ";
            getline(cin, email);
            cout << "Enter loyalty points: ";
            cin >> loyalty_points;
            if (admin.addUser(userName, password, user_id, email, loyalty_points)) {
                cout << "User added successfully!" << endl;
            } else {
                cout << "Failed to add user. Username may already exist." << endl;
            }
            break;
        case 2:
            cout << "Enter the userName to update: ";
            cin.ignore();
            getline(cin, userName);
            cout << "Enter new password: ";
            cin >> newPassword;
            if (admin.updateUser(userName, newPassword)) {
                cout << "User updated successfully!" << endl;
            } else {
                cout << "Failed to update user. Username may not exist." << endl;
            }
            break;
        case 3:
            cout << "Enter the userName to delete: ";
            cin.ignore();
            getline(cin, userName);
            if (admin.deleteUser(userName)) {
                cout << "User deleted successfully!" << endl;
            } else {
                cout << "Failed to delete user. Username may not exist." << endl;
            }
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }
}







/************************************************************************ End of Managing Users ************************************************************************/