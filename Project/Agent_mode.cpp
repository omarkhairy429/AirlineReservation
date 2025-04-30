#include "Agent_mode.hpp"


void AgentMode::startAgentMode() {
    BookingAgent agent;
    string username, password;

    cout << "--- Booking Agent Login ---" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    // Assuming a valid login check is needed here
    if (agent.Login(username, password)) {
            while(true) {
            int choice;
            cout << endl << "Login Successful" << endl << endl;
            cout << "--- Booking Agent Menu ---" << endl;
            cout << "1. Search Flights" << endl;
            cout << "2. Book a Flight" << endl;
            cout << "3. Modify Reservation" << endl;
            cout << "4. Cancel Reservation" << endl;
            cout << "5. Logout" << endl;
            cout << "Enter choice: ";
            cin >> choice;

            switch(choice) {
                case 1:  // Search Flights
                    searchFlight(agent);
                    break;
                case 2:  // Book a Flight
                    bookFlight(agent);
                    break;
                case 3:  // Modify Reservation
                    cout << "You selected: Modify Reservation" << endl;
                    // Call the function for modifying reservations here
                    break;
                case 4:  // Cancel Reservation
                    cout << "You selected: Cancel Reservation" << endl;
                    // Call the function for canceling reservations here
                    break;
                case 5:  // Logout
                    cout << "You selected: Logout" << endl;
                    cout << "Logging out..." << endl;
                    return;
                    break;
                default:
                    cout << "Invalid choice. Please select a valid option." << endl;
                    break;
            }
        }
    } else {
        cout << "Login failed! Please check your credentials." << endl;
    }
}



/***********************************************  Option 1 Book Flight **********************************************/

void AgentMode:: bookFlight(BookingAgent & agent) {
        int passengerID;
        string flightNumber, seatNumber, paymentMethod, paymentDetails;
        cout << "-- Book a Flight --" << endl << endl;

        cout << "Enter Passenger ID: ";
        cin >> passengerID;

        cout << "Enter Flight Number: ";
        cin >> flightNumber;

        cout << "Enter Seat Number (e.g., 12A): ";
        cin >> seatNumber;

        cout << "Enter Payment Method (Credit Card/Cash/PayPal): ";
        cin >> paymentMethod;

        cout << "Enter Payment Details: ";
        cin >> paymentDetails;

        if (agent.bookFlight(passengerID, flightNumber, seatNumber, paymentMethod, paymentDetails)) {
            cout << "\nBooking successful!" << endl;
            cout << "Passenger ID: " << passengerID << endl;
            cout << "Flight Number: " << flightNumber << endl;
            cout << "Seat Number: " << seatNumber << endl;
            cout << "Payment Method: " << paymentMethod << endl;
            cout << "Payment Details: " << paymentDetails << endl;
        }
        else {
            cout << "Please try again" << endl;
        }
}

/***********************************************  Option 2 Search Flight **********************************************/
void AgentMode:: searchFlight(BookingAgent & agent) {
    string origin, destination, depratureDate;
    cout << "--- Search Flights ---" << endl;
    cout << "Enter Origin: ";
    cin >> origin;
    cout << "Enter Destination: ";
    cin >> destination;
    cout << "Enter Deprature Date (YYYY-MM-DD)";
    cin >> depratureDate;
    agent.searchFlights(origin, destination, depratureDate);
}


   
