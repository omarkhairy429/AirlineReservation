#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include <string>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class Aircraft {
private:
    string model;
    string id;
    int capacity;
    double maxSpeed;

public:
    Aircraft(string m, string id, int cap, double speed);
    Aircraft() = default;

    void setModel(string m);
    void setId(string i);
    void setCapacity(int cap);
    void setMaxSpeed(double speed);

    string getModel() const;
    string getId() const;
    int getCapacity() const;
    double getMaxSpeed() const;

    void displayInfo();

    friend void to_json(json& j, const Aircraft& a) {
        j = json{
            {"model", a.model},
            {"id", a.id},
            {"capacity", a.capacity},
            {"maxSpeed", a.maxSpeed}
        };
    }
    
    friend void from_json(const json& j, Aircraft& a) {
        j.at("model").get_to(a.model);
        j.at("id").get_to(a.id);
        j.at("capacity").get_to(a.capacity);
        j.at("maxSpeed").get_to(a.maxSpeed);
    }
};

#endif
