#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "User.hpp"
#include "UserStruct.hpp"
#include "json.hpp"
#include <vector>
#include <string>
#include "Passenger.hpp"


class Admin : public User {
private:
    vector<Passenger> users;
    void loadUsers();
    void saveUsers();
    // string hashPassword(const string &password);
    // bool verifyPassword(const string &password, const string &hashedPassword);

public:
    bool Login(string userName, string password) override;
    bool addUser(string userName, string password);
    bool updateUser(string userName, string newPassword);
    bool deleteUser(string userName);
    bool logUser(string userName, string password);
};

#endif