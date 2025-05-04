#ifndef PILOT_HPP
#define PILOT_HPP

#include <string>
#include <memory>
#include "Flight.hpp"
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

class Pilot {
    public: // should be modified as private
        string pilotID;
        string pilotName;
        string assignedFlightID;
    public:

    friend void to_json(json& j, const Pilot& p) {
        j = json{
            {"pilotID", p.pilotID},
            {"pilotName", p.pilotName}
        };
    }
        
    friend void from_json(const json& j, Pilot& p) {
        j.at("pilotID").get_to(p.pilotID);
        j.at("pilotName").get_to(p.pilotName);
    }
};

#endif