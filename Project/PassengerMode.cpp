#include "PassengerMode.hpp"
#include <iostream>
using namespace std;



/******************************************* Start of Passenger Mode  *******************************************/
void PassengerMode::startPassengerMode() {
    Passenger passenger;
    string userName, password;
    vector<shared_ptr<User>> users;
    cin.ignore(); // Clear the input buffer
    cout << "Enter your username: ";
    getline(cin, userName); // Use getline to allow spaces in username
    cout << "Enter your password: ";
    cin >> password;
    if (passenger.Login(userName, password)) {
        cout << "Login successful!" << endl;
        loadUsers(users, "user.json");
        auto user_it = find_if(users.begin(), users.end(), [&](const shared_ptr<User>& user) {
            return user->getUserName() == userName;
        });
        auto it = dynamic_pointer_cast<Passenger>(*user_it);
        passenger.setUserId(it->getUserId());
        passenger.setEmail(it->getEmail());
        passenger.setLoyaltyPoints(it->getLoyaltyPoints());
        passenger.setBalance(it->getBalance());
        passenger.setUserName(it->getUserName());
        
        while (true) {
            int choice;
            cout << "\n--- Passenger Menu ---" << endl;
            cout << "1. Search Flights" << endl;
            cout << "2. Check In" << endl;
            cout << "3. View Reservations" << endl;
            cout << "4. Deposit Money" << endl;
            cout << "5. Logout" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    searchFlights(passenger); 
                    break;
                case 2:
                    checkIn(passenger); 
                    break;
                case 3:
                    cout << endl << endl;
                    viewReservations(passenger);
                    break;
                case 4:
                    cout << endl;
                    depositMoney(passenger);
                    break;
                case 5:
                    cout << "Logging out..." << endl;
                    return;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    } else {
        cout << "Login failed. Please check your username and password." << endl << endl;
    }
}


void PassengerMode::searchFlights(Passenger& passenger) {
    BookingAgent agent;
    // handlge vid getline not cin
    cin.ignore(); // Clear the input buffer
    string origin, destination, departureDate;
    cout << "Enter origin: ";
    getline(cin, origin); // Use getline to allow spaces in origin
    cout << "Enter destination: ";
    getline(cin, destination); // Use getline to allow spaces in destination
    cout << "Enter departure date (YYYY-MM-DD): ";
    getline(cin, departureDate); // Use getline to allow spaces in departure date
    if (agent.searchFlights(origin, destination, departureDate)) {
        cout << "Do you want to book a flight? (yes/no): ";
        string choice;
        cin >> choice;
        if(choice == "yes") {
            bookFlight(passenger); // Call the bookFlight function to proceed with booking
        } else {
            cout << "Booking skipped." << endl << endl;
            return;
        }
    }

    else {
        cout << "No flights found" << endl;
        return;
    }
    



}


/******************************************* Book a flight after Search  *******************************************/
void PassengerMode::bookFlight(Passenger& passenger) {
   BookingAgent agent;
    string flightNumber, seatNumber, paymentMethod, paymentDetails, reservationID;
    cout << "Enter Flight Number: ";
    cin >> flightNumber;
    cout << "Enter Seat Number (e.g., 12A): ";
    cin >> seatNumber;
    // Paymen method can be Credit Card space sep
    cout << "Enter Payment Method (Credit Card/Cash/PayPal): ";
    cin.ignore();
    getline(cin, paymentMethod); // Use getline to allow spaces in payment method
    cout << "Enter Payment Details: ";
    getline(cin, paymentDetails); // Use getline to allow spaces in payment details
    cout << "Enter Reservation ID: ";
    cin >> reservationID;
    

    

    if (agent.bookFlight(passenger.getUserId(), flightNumber, seatNumber, paymentMethod, paymentDetails, reservationID)) {
        cout << "Flight booked successfully!" << endl;
    } else {
        cout << "Failed to book flight." << endl;
    }
}

/******************************************* View Reservations  *******************************************/
void PassengerMode::viewReservations(Passenger& passenger) {
    BookingAgent agent;
    vector<shared_ptr<Reservation>> reservations;
    loadData<Reservation>(reservations, "reservations.json");

    bool found = false; // Flag to track if any reservations are found

    // Iterate through reservations and check for matching passenger ID
    for (const auto& reservation : reservations) {
        if (reservation->getPassengerID() == passenger.getUserId()) {
            found = true;
            cout << "Reservation ID: " << reservation->getReservationID() << endl;
            cout << "Flight Number: " << reservation->getFlightNumber() << endl;
            cout << "Seat Number: " << reservation->getSeatNumber() << endl;
            cout << "Payment Method: " << reservation->getPaymentMethod() << endl;
            cout << endl << endl;
        }
    }

    // If no reservations are found, display a message
    if (!found) {
        cout << "No reservations found." << endl;
    }
}

/******************************************* Check In  *******************************************/
void PassengerMode::checkIn(Passenger& passenger) {

    cout << "Enter Reservation ID: ";
    string reservationId;
    cin >> reservationId;
    cout << endl << endl; 
    if (passenger.checkIn(reservationId, passenger.getUserId())) {
        cout << "Check-in successful!" << endl;
    } else {
        cout << "Check-in failed." << endl;
    }
}


/******************************************* Deposit Money  *******************************************/
void PassengerMode::depositMoney(Passenger& passenger) {
    double amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    if (passenger.deposit(amount, passenger.getUserName())) {
        cout << "Deposit successful!" << endl << endl;
    } else {
        cout << "Deposit failed." << endl;
    }
}
