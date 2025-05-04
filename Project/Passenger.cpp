#include "Passenger.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>
#include "Admin.hpp"

using namespace std;
using json = nlohmann::json;

bool Passenger::Login(string userName, string password) {
    Admin a1;
    return(a1.logUser(userName, password));
}

bool Passenger::deposit(double amount, string username) {
    if (amount <= 0) {
        cout << "Can't deposit zero or negative numbers" << endl;
        return false;
    }
    vector <shared_ptr<User>> users;
    loadUsers(users, "user.json");
    // Deposit will work when logged in so doesn't need to check if user exists
    auto it = find_if(users.begin(), users.end(), [&](const shared_ptr<User>& user) {
        auto passenger = dynamic_pointer_cast<Passenger>(user);
        return passenger->userName == username;
    });

    shared_ptr<Passenger> passenger = dynamic_pointer_cast<Passenger>(*it);
    passenger->balance = balance + amount;
    saveUsers(users, "user.json");
    return true;
}




void Passenger:: searchFlights(string origin, string destination, string depratureDate) {
    
}

