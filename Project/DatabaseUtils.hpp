#ifndef DATABASE_UTILS_HPP
#define DATABASE_UTILS_HPP

#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;


template <typename T>
void loadData(std::vector<std::shared_ptr<T>>& data, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::ofstream createFile(filename); 
        return;
    }

    try {
        json j;
        file >> j;

        if (j.is_array()) {
            data.clear();
            for (const auto& item : j) {
                data.emplace_back(std::make_shared<T>(item.get<T>()));
            }
        } else {
            std::cerr << "Error: JSON format in '" << filename << "' is incorrect. Expected an array." << std::endl;
        }
    } catch (const json::exception& e) {
        std::cerr << "Error: Failed to parse '" << filename << "'. Exception: " << e.what() << std::endl;
    }
}


template <typename T>
void saveData(const std::vector<std::shared_ptr<T>>& data, const std::string& filename) {
    json j;
    for (const auto& item : data) {
        j.emplace_back(*item);  
    }

    std::ofstream file(filename);
    file << j.dump(4);  
}

#endif 
