#ifndef USER_DATABASE_UTILS_H
#define USER_DATABASE_UTILS_H

#include <vector>
#include <memory>
#include <string>
#include "User.hpp"
#include "Passenger.hpp" 
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

void saveUsers(const vector<shared_ptr<User>>& users, const string& filename);
void loadUsers(vector<shared_ptr<User>>& users, const string& filename);

#endif // USER_DATABASE_UTILS_H
