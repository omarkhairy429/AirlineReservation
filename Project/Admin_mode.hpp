#ifndef ADMIN_MODE_HPP
#define ADMIN_MODE_HPP

#include <string>
#include "Admin.hpp"  // Include the Admin class for functionality

class AdminMode {
public:
    void startAdminMode();  // Function to start the admin mode

private:
    /*************  Managing Flights *************/
    void manageFlights(Admin &admin);  // Function to manage flights
    void addNewFlight(Admin &admin);  // Function to add a new flight

    /*************  Managing Users *************/
    void manageUsers(Admin & admin);
};

#endif // ADMIN_MODE_HPP
