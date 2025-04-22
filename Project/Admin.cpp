#include "Admin.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;
using json = nlohmann::json;

bool Admin::Login(string userName, string password) {
    return userName == "adminUser" && password == "12345";
}

bool Admin::addUser(string userName, string password) {
    loadUsers();

    // Check if username is not taken
    auto it = find_if(users.begin(), users.end(), [&](const UserStruct& user) {
        return user.username == userName;
    });

    // Name already exists
    if (it != users.end()) {
        return false;
    }

    users.push_back({userName, password});
    saveUsers();
    return true;
}

void Admin::saveUsers() {
    json j = users;
    ofstream file("user.json");
    file << j.dump(4);
}

void Admin::loadUsers() {
    ifstream file("user.json");
    if (file.is_open()) {
        json j;
        file >> j;
        users = j.get<vector<UserStruct>>();
    }
}

bool Admin::deleteUser(string userName) {
    loadUsers();

    auto it = find_if(users.begin(), users.end(), [&](const UserStruct& user) {
        return user.username == userName;
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

    auto it = find_if(users.begin(), users.end(), [&](UserStruct& user) {
        return user.username == userName;
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
