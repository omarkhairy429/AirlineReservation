#include "FlightAttendantDatabaseUtils.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void loadFlightAttendants(vector<shared_ptr<FlightAttendant>>& attendants, const string& filename) {
    ifstream file(filename);
    if (!file) {
        ofstream createFile(filename);  // Create the file if it doesn't exist
        return; 
    }

    try {
        json j;
        file >> j;

        if (j.is_array()) {
            attendants.clear();
            for (const auto& item : j) {
                attendants.emplace_back(make_shared<FlightAttendant>(item.get<FlightAttendant>()));
            }
        } else {
            cerr << "Error: JSON format is incorrect. Expected an array." << endl;
        }
    } catch (const json::exception& e) {
        cerr << "Error: Failed to parse " << filename << " file. Exception: " << e.what() << endl;
    }
}

void saveFlightAttendants(const vector<shared_ptr<FlightAttendant>>& attendants, const string& filename) {
    json j;
    for (const auto& attendant : attendants) {
        j.emplace_back(*attendant); 
    }

    ofstream file(filename);
    file << j.dump(4);
}

