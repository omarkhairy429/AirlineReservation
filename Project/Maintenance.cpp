#include "Maintenance.hpp"

// Default Constructor
Maintenance::Maintenance() : estimatedCost(0.0) {}

// Parameterized Constructor
Maintenance::Maintenance(const std::string& aircraftId, const std::string& maintenanceType,
                         const std::string& startDate, const std::string& endDate,
                         const std::string& description, double estimatedCost)
    : aircraftId(aircraftId), maintenanceType(maintenanceType),
      startDate(startDate), endDate(endDate), description(description),
      estimatedCost(estimatedCost) {}

// Getters
std::string Maintenance::getAircraftId() const {
    return aircraftId;
}

std::string Maintenance::getMaintenanceType() const {
    return maintenanceType;
}

std::string Maintenance::getStartDate() const {
    return startDate;
}

std::string Maintenance::getEndDate() const {
    return endDate;
}

std::string Maintenance::getDescription() const {
    return description;
}

double Maintenance::getEstimatedCost() const {
    return estimatedCost;
}

// Setters
void Maintenance::setAircraftId(const std::string& id) {
    aircraftId = id;
}

void Maintenance::setMaintenanceType(const std::string& type) {
    maintenanceType = type;
}

void Maintenance::setStartDate(const std::string& date) {
    startDate = date;
}

void Maintenance::setEndDate(const std::string& date) {
    endDate = date;
}

void Maintenance::setDescription(const std::string& desc) {
    description = desc;
}

void Maintenance::setEstimatedCost(double cost) {
    estimatedCost = cost;
}
