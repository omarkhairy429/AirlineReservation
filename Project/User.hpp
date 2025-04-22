#ifndef USER_HPP
#define USER_HPP

#include <iostream>

using namespace std;

class User {
protected:
    string userName;
    string password;

public:
    virtual bool Login(string userName, string password) = 0;
};

#endif
