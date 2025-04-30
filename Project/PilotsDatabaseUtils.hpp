#ifndef USER_DATABASE_UTILS_H
#define USER_DATABASE_UTILS_H

#include <vector>
#include <memory>
#include <string>
#include "Pilot.hpp"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

void savePilots(const vector<shared_ptr<Pilot>>& pilots, const string& filename);
void loadPilots(vector<shared_ptr<Pilot>>& pilots, const string& filename);

#endif // USER_DATABASE_UTILS_H
