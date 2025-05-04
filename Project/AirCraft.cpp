#include "Aircraft.hpp"
#include <iostream>

using namespace std;

// Constructor implementation
Aircraft::Aircraft(string m, string id, int cap, double speed) {
    model = m;
    capacity = cap;
    maxSpeed = speed;
    this->id = id;
}

// Setters
void Aircraft::setModel(string m) {
    model = m;
}

void Aircraft::setId(string i) {
    id = i;
}

void Aircraft::setCapacity(int cap) {
    capacity = cap;
}

void Aircraft::setMaxSpeed(double speed) {
    maxSpeed = speed;
}

// Getters
string Aircraft::getModel() const {
    return model;
}

string Aircraft::getId() const {
    return id;
}

int Aircraft::getCapacity() const {
    return capacity;
}

double Aircraft::getMaxSpeed() const {
    return maxSpeed;
}

// Method to display aircraft info
void Aircraft::displayInfo() {
    cout << "Model: " << model << endl;
    cout << "ID: " << id << endl;
    cout << "Capacity: " << capacity << " passengers" << endl;
    cout << "Max Speed: " << maxSpeed << " km/h" << endl;
}
