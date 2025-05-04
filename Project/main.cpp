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






/********************************************************* Start of Main Function  ****************************************************/
int main() {
    AdminMode admin;
    AgentMode agent;
    while(true) {
      int choice;
      cout << "Welcome to Airline Reservation and Management System" << endl;
      cout << "Please select your role: " << endl;
      cout << "1. Administrator" << endl;
      cout << "2. Booking Agent" << endl;
      cout << "3. Passenger" << endl;
      cout << "4. Exit" << endl;
      cout << "Enter choice: ";
      cin >> choice;
      cout << endl;

      switch (choice) {
          case 1:
              admin.startAdminMode();
              break;
          case 2:
              agent.startAgentMode();
              break;
          case 3:
              //passenger();
              break;
          case 4:
            return 0;
          default:
              cout << "Enter a valid choice" << endl;
              break;
      }

    }
    return 0;
}


/********************************************************* End of Main Function  ****************************************************/

