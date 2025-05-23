#ifndef PASSENGER_HPP
#define PASSENGER_HPP

#include "User.hpp"
#include "json.hpp"
#include <vector>
#include "checkIn.hpp"
#include "Reservation.hpp"

class Admin;

using json = nlohmann::json;

class Passenger : public User {
private:
    int user_id;
    std::string email;
    int loyalty_points;
    double balance;
    vector<shared_ptr<CheckIn>> checks;
    vector<shared_ptr<Reservation>> reservations; 

public:
    Passenger() : balance(0) {}

    Passenger(std::string userName, std::string password, int user_id, std::string email, int loyalty_points)
        : User(userName, password), user_id(user_id), email(email), loyalty_points(loyalty_points), balance(0) {}

    bool Login(std::string userName, std::string password) override;

    // Getters
    int getUserId() const { return user_id; }
    std::string getEmail() const { return email; }
    int getLoyaltyPoints() const { return loyalty_points; }
    double getBalance() const { return balance; }

    // Setters
    void setUserId(int id) { user_id = id; }
    void setEmail(const std::string& email) { this->email = email; }
    void setLoyaltyPoints(int points) { loyalty_points = points; }
    void setBalance(double bal) { balance = bal; }

    // Additional functionality
    bool deposit(double amount, std::string username);
    bool checkIn(const string & reservationId, int user_id);

    // JSON Serialization
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

#endif // PASSENGER_HPP
