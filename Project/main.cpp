#include <iostream>
#include <fstream>
#include "User.hpp"
#include "Admin.hpp"
#include "Passenger.hpp"
#include "BookingAgent.hpp"
#include "json.hpp"
using namespace std;



int main() {

  // Passenger p1;
  // p1.SignIn("Mohamed", "123");

  Admin a1;
  Passenger p1;
  p1.Login("Omar", "123");

  // if(a1.Login("adminUser", "12345")) {
  //   a1.updateUser("Ahmed", "#Omarqwer1#232310");
  // }

  
    

    // User user1;
    // user1.Login("Omar", "123");
    // cout << user1.getUserName() << endl;

    // Admin admin1;
    // admin1.Login("Admin", "123");
    // cout << admin1.getUserName() << endl;

    // Admin b1;
    // b1.Login("Agent", "123");
    // cout << b1.getUserName() << endl;
}