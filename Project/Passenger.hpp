#ifndef PASSENGER_HPP
#define PASSENGER_HPP

#include "User.hpp"
#include "json.hpp"
#include <vector>

class Admin;

using json = nlohmann::json;

// Added data member balance if there is a bug in the code remove everything about it

class Passenger : public User {
private:
    int user_id;
    string email;
    int loyalty_points;
    double balance;


public:
    Passenger(): balance(0) {};
    Passenger(string userName, string password, int user_id, string email, int loyalty_points)
        :User(userName, password), user_id(user_id), email(email), loyalty_points(loyalty_points) {}

    bool Login(std::string userName, std::string password) override;
    void searchFlights(string origin, string destination, string departureDate);

    int getUserId() const { return user_id; }
    void setUserId(int id) { user_id = id; }

    string getEmail() const { return email; }
    void setEmail(const string& email) { this->email = email; }

    int getLoyaltyPoints() const { return loyalty_points; }
    void setLoyaltyPoints(int points) { loyalty_points = points; }

    //double getBalance() const   {return balance;} 
    bool deposit(double amount, string username);

    friend void to_json(json& j, const Passenger& p) {
        j = json{
            {"userName", p.userName},
            {"password", p.password},
            {"user_id", p.user_id},
            {"email", p.email},
            {"loyalty_points", p.loyalty_points},
            {"balance", p.balance}
        };
    }
    
    friend void from_json(const json& j, Passenger& p) {
        j.at("userName").get_to(p.userName);
        j.at("password").get_to(p.password);
        j.at("user_id").get_to(p.user_id);
        j.at("email").get_to(p.email);
        j.at("loyalty_points").get_to(p.loyalty_points);
        j.at("balance").get_to(p.balance);
    }
    
    friend class BookingAgent;
};

#endif
