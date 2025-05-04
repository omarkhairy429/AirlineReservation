#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

class User {
protected:
    string userName;
    string password;

public:
    // Default Constructor
    User() = default;

    // Parameterized Constructor
    User(string userName, string password) : userName(userName), password(password) {}

    // Pure virtual function for Login
    virtual bool Login(string userName, string password) = 0;

    // Getters
    string getUserName() const { return userName; }
    string getPassword() const { return password; }

    // Setters
    void setUserName(const string& userName) { this->userName = userName; }
    void setPassword(const string& password) { this->password = password; }

    // Friend functions for JSON serialization
    friend void to_json(json& j, const User& p) {
        j = json{{"userName", p.userName}, {"password", p.password}};
    }

    friend void from_json(const json& j, User& p) {
        j.at("userName").get_to(p.userName);
        j.at("password").get_to(p.password);
    }

    // Friend classes
    friend class Admin;
};

#endif