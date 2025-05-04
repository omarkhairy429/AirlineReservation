#include "PilotsDatabaseUtils.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void savePilots(const vector<shared_ptr<Pilot>>& pilots, const string& filename) {
    json j;
    for (const auto& pilot : pilots) {
        j.emplace_back(*pilot);
    }

    ofstream file(filename);
    file << j.dump(4);
}

void loadPilots(vector<shared_ptr<Pilot>>& pilots, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open " << filename << " file." << endl;
        return;
    }

    try {
        json j;
        file >> j;

        if (j.is_array()) {
            pilots.clear();
            for (const auto& item : j) {
                pilots.push_back(make_shared<Pilot>(item.get<Pilot>()));
            }
        } else {
            cerr << "Error: JSON format is incorrect. Expected an array." << endl;
        }
    } catch (const json::exception& e) {
        cerr << "Error: Failed to parse " << filename << " file. Exception: " << e.what() << endl;
    }
}
