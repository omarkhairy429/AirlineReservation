#include "Passenger.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;
using json = nlohmann::json;

bool Passenger::Login(string userName, string password) {
    loadUsers();
    auto it = find_if(users.begin(), users.end(), [&](const UserStruct& user) {
        return user.username == userName && user.password == password;
    });

    if (it != users.end()) {
        cout << "User Logged in Successfully" << endl;
        return true;
    }

    cout << "Wrong User name or Password" << endl;
    return false;
}

void Passenger::loadUsers() {
    ifstream file("user.json");
    if (file.is_open()) {
        json j;
        file >> j;
        users = j.get<vector<UserStruct>>();
    }
}
