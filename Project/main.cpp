#include <iostream>
#include <fstream>
#include "User.hpp"
#include "Admin.hpp"
#include "Passenger.hpp"
#include "BookingAgent.hpp"
#include "json.hpp"
using namespace std;

#define ADMIN_MODE 1
#define BOOKINGAGENT_MODE 2
#define PASSENGER_MODE 3
#define EXIT 4

// Admin
#define MANAGE_FLIGHTS 1
#define MANAGE_AIRCRAFT 2
#define MANAGE_USERS 3
#define GENERATE_REPORTS 4
#define LOGOUT 5

// Admin Manage Flights
#define ADD_NEW_FLIGHT 1
#define UPDATE_EXISTING_FLIGHT 2
#define REMOVE_FLIGHT 3
#define VIEW_ALL_FLIGHTS 4
#define BACK_TO_MAIN_MENU 5


void adminMode();
void bookingAgent();
void passenger();

// Modes Inside Admin Mode
void manageFlights(Admin & admin);

// Functions for Managing Flights
void addNewFlight(Admin & admin);

/********************************************************* Start of Main Function  ****************************************************/
int main() {

//     while(true) {
//       int choice;
//       cout << "Welcome to Airline Reservation and Management System" << endl;
//       cout << "Please select your role: " << endl;
//       cout << "1. Administrator" << endl;
//       cout << "2. Booking Agent" << endl;
//       cout << "3. Passenger" << endl;
//       cout << "4. Exit" << endl;
//       cout << "Enter choice: ";
//       cin >> choice;
//       cout << endl;

//       switch (choice) {
//           case ADMIN_MODE:
//               adminMode();
//               break;
//           case BOOKINGAGENT_MODE:
//               bookingAgent();
//               break;
//           case PASSENGER_MODE:
//               passenger();
//               break;
//           case EXIT:
//             return 0;
//           default:
//               cout << "Enter a valid choice" << endl;
//               break;
//       }
//   }
//   return 0;

    BookingAgent b1;
    b1.searchFlights("Egypt", "Germany", "2025-06-10 20:30");
}
/********************************************************* End of Main Function  ****************************************************/


/********************************************************************  Start of Admin Mode ********************************************************************/
void adminMode() {
    Admin admin1;
    string username, password;
    cout << "--- Adminstrator Login ---" << endl;
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
            case MANAGE_FLIGHTS:
                manageFlights(admin1);
                break;
            case MANAGE_AIRCRAFT:
                cout << "Managing Aircraft..." << endl;
                break;
            case MANAGE_USERS:
                cout << "Managing Users..." << endl;
                break;
            case GENERATE_REPORTS:
                cout << "Generating Reports..." << endl;
                break;
            case LOGOUT:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
                break;
        }
    }
}

///////////////////////////////////////////////////////////// Manage Flights mode
void manageFlights(Admin & admin) {
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
        case ADD_NEW_FLIGHT:
          addNewFlight(admin);
          break;
        case UPDATE_EXISTING_FLIGHT:
            cout << "Updating an existing flight..." << endl;
            break;
        case REMOVE_FLIGHT:
            cout << "Removing a flight..." << endl;
            break;
        case VIEW_ALL_FLIGHTS:
            cout << "Viewing all flights..." << endl;
            break;
        case BACK_TO_MAIN_MENU:
            cout << "Going back to the main menu..." << endl;
            break;
        default:
            cout << "Invalid choice. Please select a valid option." << endl;
            break;
    }

}

// First Function in managing Flights
void addNewFlight(Admin & admin) {
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

    admin.addFlight(flightNumber, origin, destination, departureDateTime, arrivalDateTime, status);
}


/******************************************************************** End of Admin Mode ********************************************************************/

void bookingAgent() {}

void passenger() {}
