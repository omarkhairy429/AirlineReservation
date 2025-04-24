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

