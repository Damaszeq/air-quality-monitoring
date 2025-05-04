#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <vector>
#include <string>
#include "Station.h"
#include "Sensor.h"
#include "AirQualityIndex.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

class DatabaseManager {
public:
    // Metoda zapisująca dane do pliku JSON
    static void saveToDatabase(const Station& station, const AirQualityIndex& airQualityIndex, const std::vector<Sensor>& sensors, const std::string& filePath);
};

#endif // DATABASEMANAGER_H
