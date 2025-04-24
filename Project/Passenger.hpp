#ifndef PASSENGER_HPP
#define PASSENGER_HPP

#include "User.hpp"
#include "json.hpp"
#include <vector>

using json = nlohmann::json;
class Admin;

class Passenger : public User {
private:

public:
    Passenger() = default;
    Passenger(string userName, string password): User(userName, password) {}
    bool Login(std::string userName, std::string password) override;
      // JSON serialization and deserialization
  
    friend void to_json(json& j, const Passenger& p) {
        j = json{{"userName", p.userName}, {"password", p.password}};
    }

    friend void from_json(const json& j, Passenger& p) {
        j.at("userName").get_to(p.userName);
        j.at("password").get_to(p.password);
    }
    friend class Admin;
};

#endif
