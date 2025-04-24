#include <iostream>
#include "BookingAgent.hpp"
#include "fstream"

bool BookingAgent::Login(string userName, string password) {
    if (userName == "agentUser" && password == "12345") {
        this->userName = userName;
        this->password = password;
        return true;
    }
    return false;

    
}



/******************************** Start of Booking Agent Flight Operations  **************************************************/

void BookingAgent::loadFlights() {
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

void BookingAgent::saveFlights() {
    json j;
    for (const auto& flight : Flights) {
        j.emplace_back(*flight); 
    }
    
    ofstream file("Flights.json");
    file << j.dump(4);
}

/* Search in Flights database  */
void BookingAgent::searchFlights(string origin, string destination, string depratureDate) {
    loadFlights();
    int counter = 0;
    for(const auto& flight : Flights) {
        // Example output
        if (flight->origin == origin && flight->destination == destination && flight->depratureTime == depratureDate) {
            counter++;
            cout << counter << ". " << "Flight Number: " << flight->flightNumber << endl;
            cout << "   Deprature: " << flight->depratureTime << endl;
            cout << "   Arrival: " << flight->arrivalTime<< endl;
            // Available seats to be added
            // Price to be added
        }
    }
    if (counter == 0) {
        cout << "There is no available Flights right now -_-" << endl;
    }
}


/******************************** End of Booking Agent Flight Operations  **************************************************/
