#include "UserDatabaseUtils.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void saveUsers(const vector<shared_ptr<User>>& users, const string& filename) {
    json j;
    for (const auto& user : users) {
        if (auto passenger = dynamic_pointer_cast<Passenger>(user)) {
            j.emplace_back(*passenger);
        } else {
            j.emplace_back(*user);
        }
    }

    ofstream file(filename);
    file << j.dump(4);
}

void loadUsers(vector<shared_ptr<User>>& users, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open " << filename << " file." << endl;
        return;
    }

    try {
        json j;
        file >> j;

        if (j.is_array()) {
            users.clear();
            for (const auto& item : j) {
                users.push_back(make_shared<Passenger>(item.get<Passenger>()));
            }
        } else {
            cerr << "Error: JSON format is incorrect. Expected an array." << endl;
        }
    } catch (const json::exception& e) {
        cerr << "Error: Failed to parse " << filename << " file. Exception: " << e.what() << endl;
    }
}
