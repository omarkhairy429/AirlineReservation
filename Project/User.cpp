#include "User.hpp"

string User:: getUserName() const {
    return userName;
}

string User:: getPassword() const {
    return password; 
}
        
void User::setUserName(string userName) {
    this->userName  = userName;
}

void User:: setPassword(string password) {
    this->password = password;
}






