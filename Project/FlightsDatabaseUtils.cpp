#include "FlightsDatabaseUtils.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void loadFlights(vector<shared_ptr<Flight>>& Flights, const string& filename) {
    ifstream file(filename);
    if (!file) {
        ofstream createFile(filename);  // Create the file if it doesn't exist
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
        cerr << "Error: Failed to parse " << filename << " file. Exception: " << e.what() << endl;
    }
}

void saveFlights(const vector<shared_ptr<Flight>>& Flights, const string& filename) {
    json j;
    for (const auto& flight : Flights) {
        j.emplace_back(*flight); 
    }
    
    ofstream file(filename);
    file << j.dump(4);
}
