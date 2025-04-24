#include "Admin.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;
using json = nlohmann::json;

/* Admin login */
bool Admin::Login(string userName, string password) {
    return userName == "adminUser" && password == "12345";
}

bool Admin::addUser(string userName, string password) {
    loadUsers();

    // Check if username is not taken
    auto it = find_if(users.begin(), users.end(), [&](const Passenger& user) {
        return user.userName == userName;
    });

    // Name already exists
    if (it != users.end()) {
        return false;
    }

    users.emplace_back(Passenger(userName, password));
    saveUsers();
    return true;
}

void Admin::saveUsers() {
    json j = users;
    ofstream file("user.json");
    file << j.dump(4);
}

void Admin::loadUsers() {
    // Open the file with an ifstream object
    ifstream file("user.json");
    
    // Check if the file is open
    if (!file.is_open()) {
        cerr << "Error: Unable to open user.json file." << endl;
        return;
    }

    try {
        // Parse the file contents into a JSON object
        json j;
        file >> j;

        // Check if the JSON is not empty and has the correct structure
        if (j.is_array()) {
            // Assign the parsed JSON array to users vector
            users = j.get<vector<Passenger>>();
        } else {
            cerr << "Error: JSON format is incorrect. Expected an array." << endl;
        }
    } catch (const json::exception& e) {
        // Catch JSON parsing errors
        cerr << "Error: Failed to parse user.json file. Exception: " << e.what() << endl;
    } catch (const bad_alloc& e) {
        // Catch bad allocation errors (out of memory)
        cerr << "Error: Memory allocation failed while loading users. Exception: " << e.what() << endl;
    } catch (...) {
        // Catch any other unforeseen errors
        cerr << "An unknown error occurred while loading users." << endl;
    }
}


bool Admin::deleteUser(string userName) {
    loadUsers();

    auto it = find_if(users.begin(), users.end(), [&](const Passenger& user) {
        return user.userName == userName;
    });

    if (it != users.end()) {
        users.erase(it);
        saveUsers();
        return true;
    }

    return false;
}

bool Admin::updateUser(string userName, string newPassword) {
    loadUsers();

    auto it = find_if(users.begin(), users.end(), [&](Passenger& user) {
        return user.userName == userName;
    });

    if (it != users.end()) {
        if (newPassword == it->password) {
            cout << "Enter a new password" << endl;
            return false;
        }

        it->password = newPassword;
        saveUsers();
        return true;
    }

    cout << "User name doesn't exist" << endl;
    return false;
}


bool Admin::logUser(string userName, string password) {
    loadUsers();
    auto it = find_if(users.begin(), users.end(), [&](const Passenger& user) {
        return user.userName == userName && user.password == password;
    });

    if (it != users.end()) {
        cout << "User Logged in Successfully" << endl;
        return true;
    }

    cout << "Wrong User name or Password" << endl;
    return false;
}
