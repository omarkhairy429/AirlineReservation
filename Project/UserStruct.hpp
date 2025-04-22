#ifndef USERSTRUCT_HPP
#define USERSTRUCT_HPP

#include "json.hpp"
#include <string>

using namespace std;
using json = nlohmann::json;

struct UserStruct {
    string username;
    string password;
};

inline void to_json(json &j, const UserStruct &u) {
    j["username"] = u.username;
    j["password"] = u.password;
}

inline void from_json(const json &j, UserStruct &u) {
    u.username = j.at("username").get<string>();
    u.password = j.at("password").get<string>();
}

#endif