#include "FlightAttendantDatabaseUtils.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void saveFlightAttendants(const vector<shared_ptr<FlightAttendant>>& attendants, const string& filename) {
    json j;
    for (const auto& attendant : attendants) {
        j.emplace_back(attendant);
    }

    ofstream file(filename);
    file << j.dump(4);
}

void loadFlightAttendants(vector<shared_ptr<FlightAttendant>>& attendants, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open " << filename << " file." << endl;
        return;
    }

    try {
        json j;
        file >> j;

        if (j.is_array()) {
            attendants.clear();
            for (const auto& item : j) {
                attendants.push_back(make_shared<FlightAttendant>(item.get<FlightAttendant>()));
            }
        } else {
            cerr << "Error: JSON format is incorrect. Expected an array." << endl;
        }
    } catch (const json::exception& e) {
        cerr << "Error: Failed to parse " << filename << " file. Exception: " << e.what() << endl;
    }
}
