#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <string>
#include <vector>
#include "Station.h"
#include "Sensor.h"
#include "Measurement.h"
#include "AirQualityIndex.h"

class DatabaseManager {
public:
bool fileExistsAndNotEmpty(const std::string& filename);
    // Funkcja do zapisywania danych do bazy
    void saveToDatabase(const Station& station, const AirQualityIndex& aqi, 
                        const std::vector<Sensor>& sensors, const std::string& filePath);

    // Funkcja do ładowania stacji z bazy
    std::vector<Station> loadFromDatabase(const std::string& filePath);

    // Funkcja do ładowania danych sensorów z bazy
    std::vector<Sensor> loadSensorDataFromDatabase(const std::string& filePath, int stationId);

    // Funkcja do zapisywania pomiarów dla sensorów
    void saveMeasurementData(string stationName, string sensorName, const std::vector<Measurement>& measurements);
};

#endif // DATABASEMANAGER_H
