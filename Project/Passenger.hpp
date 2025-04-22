#ifndef PASSENGER_HPP
#define PASSENGER_HPP

#include "User.hpp"
#include "UserStruct.hpp"
#include "json.hpp"
#include <vector>

class Passenger : public User {
private:
    std::vector<UserStruct> users;
    void loadUsers();

public:
    bool Login(std::string userName, std::string password) override;
};

#endif
