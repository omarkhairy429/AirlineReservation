#ifndef ADMIN_MODE_HPP
#define ADMIN_MODE_HPP

#include <string>
#include "Admin.hpp"  // Include the Admin class for functionality
#include <fstream>

class AdminMode {
public:
    void startAdminMode();  // Function to start the admin mode

private:
    /*************  Managing Flights *************/
    void manageFlights(Admin &admin);  // Function to manage flights
    void addNewFlight(Admin &admin);  // Function to add a new flight

    /*************  Managing Users *************/
    void manageUsers(Admin & admin);
    void addUser(Admin &admin);  // Function to add a new user
    void updateUser(Admin &admin);  // Function to update user information
    void deleteUser(Admin &admin);  // Function to delete a user


    /*************  Managing Aircrafts *************/
    void manageAircrafts(Admin &admin);  
    void manageCrewAssignments(Admin &admin);
    void addAircraft(Admin &admin);  
    void assignAircraft(Admin &admin); 

    /* Manage Flights */
    void removeFlight(Admin &admin);  
    void updateFlight(Admin &admin);  
    void viewAllFlights(Admin &admin); 

    /* Displays */
    void displayUsers(Admin &admin);  
    void displayFlights(Admin &admin); 
    void displayAircrafts(Admin &admin);  
    void displayPilots(Admin &admin);  
    void displayFlightAttendants(Admin &admin);  
    void displayCrewAssignments(Admin &admin);  
    void displayAircraftAssignments(Admin &admin);
};

#endif // ADMIN_MODE_HPP
