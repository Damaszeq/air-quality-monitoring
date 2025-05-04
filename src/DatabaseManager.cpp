#include "DatabaseManager.h"

void DatabaseManager::saveToDatabase(const Station& station, const AirQualityIndex& airQualityIndex, const std::vector<Sensor>& sensors, const std::string& filePath) {
    // Tworzymy strukturę JSON
    nlohmann::json dbData;

    // Dodajemy dane stacji
    dbData["station"]["id"] = station.getId();
    dbData["station"]["name"] = station.getName();
    dbData["station"]["city"] = station.getCity();
    dbData["station"]["latitude"] = station.getLatitude();
    dbData["station"]["longitude"] = station.getLongitude();

    // Dodajemy dane AirQualityIndex
    dbData["airQualityIndex"]["stationId"] = airQualityIndex.getStationId();
    dbData["airQualityIndex"]["calcDate"] = airQualityIndex.getCalcDate();
    dbData["airQualityIndex"]["stIndex"] = airQualityIndex.getStIndexName();
    dbData["airQualityIndex"]["so2Index"] = airQualityIndex.getSo2IndexName();
    dbData["airQualityIndex"]["no2Index"] = airQualityIndex.getNo2IndexName();
    dbData["airQualityIndex"]["pm10Index"] = airQualityIndex.getPm10IndexName();
    dbData["airQualityIndex"]["pm25Index"] = airQualityIndex.getPm25IndexName();
    dbData["airQualityIndex"]["o3Index"] = airQualityIndex.getO3IndexName();

    // Dodajemy sensory
    for (const auto& sensor : sensors) {
        nlohmann::json sensorData;
        sensorData["id"] = sensor.getId();
        sensorData["paramName"] = sensor.getParamName();
        sensorData["paramFormula"] = sensor.getParamFormula();
        sensorData["paramCode"] = sensor.getParamCode();
        dbData["sensors"].push_back(sensorData);
    }

    // Zapisujemy dane do pliku JSON
    try {
        std::ofstream file(filePath, std::ios::app); // Otwieramy w trybie do dopisywania
        if (file.is_open()) {
            file << dbData.dump(4); // Dump do pliku w formacie ładnie sformatowanym (4 spacje)
            file << std::endl;
            file.close();
            std::cout << "Dane zostały zapisane w bazie danych.\n";
        } else {
            std::cout << "Nie udało się otworzyć pliku do zapisu.\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Błąd zapisu do pliku: " << e.what() << std::endl;
    }
}
