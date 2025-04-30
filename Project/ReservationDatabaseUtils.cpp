#include "ReservationDatabaseUtils.hpp"
#include <fstream>
#include <iostream>

void loadReservations(vector<shared_ptr<Reservation>>& reservations, const string& filePath) {
    
    ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        cerr << "Could not open the file: " << filePath << endl;
        return;
    }

    json j;
    inputFile >> j;

    reservations.clear();

    for (const auto& item : j) {
        auto reservation = make_shared<Reservation>();
        from_json(item, *reservation);
        reservations.push_back(reservation);
    }


    inputFile.close();
}

void saveReservations(const vector<shared_ptr<Reservation>>& reservations, const string& filePath) {
    ofstream outputFile(filePath);
    if (!outputFile.is_open()) {
        cerr << "Could not open the file: " << filePath << endl;
        return;
    }

    json j;
    for (const auto& reservation : reservations) {
        j.push_back(*reservation);  
    }

    outputFile << j.dump(4); 

    outputFile.close();
}
