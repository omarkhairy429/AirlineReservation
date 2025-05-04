#include "AirCraftDatabaseUtils.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void loadAircraft(vector<shared_ptr<Aircraft>>& aircrafts, const string& filename) {
    ifstream file(filename);
    if (!file) {
        ofstream createFile(filename);  // Create the file if it doesn't exist
        cout << "Created new file: " << filename << endl;
        return; 
    }

    try {
        json j;
        file >> j;

        if (j.is_array()) {
            aircrafts.clear();  // Clear existing data before loading new

            for (const auto& item : j) {
                // Check if all required fields exist and have correct types
                if (item.contains("model") && item["model"].is_string() &&
                    item.contains("capacity") && item["capacity"].is_number_integer() &&
                    item.contains("maxSpeed") && item["maxSpeed"].is_number() &&
                    item.contains("id") && item["id"].is_string()) {

                    // Add aircraft to vector
                    aircrafts.emplace_back(make_shared<Aircraft>(
                        item["model"], 
                        item["id"], 
                        item["capacity"], 
                        item["maxSpeed"]
                    ));
                } else {
                    cerr << "Error: Missing or invalid data for an aircraft entry." << endl;
                }
            }
        } else {
            cerr << "Error: JSON format is incorrect. Expected an array." << endl;
        }
    } catch (const json::exception& e) {
        cerr << "Error: Failed to parse " << filename << " file. Exception: " << e.what() << endl;
    }
}

void saveAircraft(const vector<shared_ptr<Aircraft>>& aircrafts, const string& filename) {
    json j;
    for (const auto& aircraft : aircrafts) {
        j.push_back({
            {"model", aircraft->getModel()},
            {"id", aircraft->getId()},
            {"capacity", aircraft->getCapacity()},
            {"maxSpeed", aircraft->getMaxSpeed()}
        });
    }
    
    ofstream file(filename);
    file << j.dump(4);
}
