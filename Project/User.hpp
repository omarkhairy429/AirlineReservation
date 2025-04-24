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
    User() = default;
    User(string userName, string password);
    virtual bool Login(string userName, string password) = 0;
  
    friend void to_json(json& j, const User& p) {
        j = json{{"userName", p.userName}, {"password", p.password}};
    }

    friend void from_json(const json& j, User& p) {
        j.at("userName").get_to(p.userName);
        j.at("password").get_to(p.password);
    }
    friend class Admin;


};

#endif
