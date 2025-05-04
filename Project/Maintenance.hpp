#ifndef MAINTENANCE_HPP
#define MAINTENANCE_HPP

#include <string>
#include "json.hpp"

using json = nlohmann::json;

class Maintenance {
private:
    std::string aircraftId;
    std::string maintenanceType;     // e.g., "Engine", "Avionics", etc.
    std::string startDate;           // Format: YYYY-MM-DD
    std::string endDate;             // Format: YYYY-MM-DD
    std::string description;         // Additional notes or description
    double estimatedCost;            // Optional: cost estimation in USD

public:
    // Constructors
    Maintenance();
    Maintenance(const std::string& aircraftId, const std::string& maintenanceType,
                const std::string& startDate, const std::string& endDate,
                const std::string& description, double estimatedCost);

    // Getters
    std::string getAircraftId() const;
    std::string getMaintenanceType() const;
    std::string getStartDate() const;
    std::string getEndDate() const;
    std::string getDescription() const;
    double getEstimatedCost() const;

    // Setters
    void setAircraftId(const std::string& id);
    void setMaintenanceType(const std::string& type);
    void setStartDate(const std::string& date);
    void setEndDate(const std::string& date);
    void setDescription(const std::string& desc);
    void setEstimatedCost(double cost);

    friend void to_json(json& j, const Maintenance& m) {
        j = json{
            {"aircraftId", m.aircraftId},
            {"maintenanceType", m.maintenanceType},
            {"startDate", m.startDate},
            {"endDate", m.endDate},
            {"description", m.description},
            {"estimatedCost", m.estimatedCost}
        };
    }
    
    friend void from_json(const json& j, Maintenance& m) {
        j.at("aircraftId").get_to(m.aircraftId);
        j.at("maintenanceType").get_to(m.maintenanceType);
        j.at("startDate").get_to(m.startDate);
        j.at("endDate").get_to(m.endDate);
        j.at("description").get_to(m.description);
        j.at("estimatedCost").get_to(m.estimatedCost);
    }
};

#endif // MAINTENANCE_HPP

