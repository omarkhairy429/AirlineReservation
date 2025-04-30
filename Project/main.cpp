#include <iostream>
#include <fstream>
#include "User.hpp"
#include "Admin.hpp"
#include "Passenger.hpp"
#include "BookingAgent.hpp"
#include "json.hpp"
#include "Admin_mode.hpp"
#include "Agent_mode.hpp"
#include "Pilot.hpp"
using namespace std;


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



void bookingAgent();
void passenger();


/********************************************************* Start of Main Function  ****************************************************/
int main() {
//     AdminMode admin;
//     AgentMode agent;

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
//           case 1:
//               admin.startAdminMode();
//               break;
//           case BOOKINGAGENT_MODE:
//               agent.startAgentMode();
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

//     BookingAgent b1;
//     b1.searchFlights("Egypt", "Germany", "2025-06-10 20:30");

}
/********************************************************* End of Main Function  ****************************************************/



void bookingAgent() {}

void passenger() {}
