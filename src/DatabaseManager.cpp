#include "DatabaseManager.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <sys/stat.h>  // dla sprawdzenia rozmiaru pliku

using json = nlohmann::json;

void DatabaseManager::saveToDatabase(const Station& station, const AirQualityIndex& aqi, 
    const std::vector<Sensor>& sensors, const std::string& filePath) {
json dbData;

// Załaduj istniejącą bazę danych, jeśli plik już istnieje
std::ifstream inputFile(filePath);
if (inputFile.is_open()) {
try {
inputFile >> dbData;
inputFile.close();
} catch (const std::exception& e) {
std::cerr << "Błąd podczas wczytywania danych z pliku: " << e.what() << "\n";
return;
}
}

// Dodaj nowe dane stacji i pomiarów do bazy
json stationData;
stationData["station"] = {
{"id", station.getId()},
{"name", station.getName()},
{"city", station.getCity()},
{"latitude", station.getLatitude()},
{"longitude", station.getLongitude()}
};
stationData["airQualityIndex"] = {
{"calcDate", aqi.getCalcDate()},
{"no2Index", aqi.getNo2Index()},
{"o3Index", aqi.getO3Index()},
{"pm10Index", aqi.getPm10Index()},
{"pm25Index", aqi.getPm25Index()},
{"so2Index", aqi.getSo2Index()},
{"stIndex", aqi.getStIndex()},
{"stationId", aqi.getStationId()}
};

// Dodaj dane sensorów
json sensorsData = json::array();
for (const auto& sensor : sensors) {
sensorsData.push_back({
{"id", sensor.getId()},
{"paramCode", sensor.getParamCode()},
{"paramFormula", sensor.getParamFormula()},
{"paramName", sensor.getParamName()}
});
}

// Dodaj stację, AQI i sensory do bazy
stationData["sensors"] = sensorsData;

// Zanim dodasz stację do bazy, sprawdź, czy już istnieje w bazie
bool stationExists = false;
for (const auto& entry : dbData) {
if (entry["station"]["id"] == station.getId()) {
stationExists = true;
break;
}
}

if (!stationExists) {
dbData.push_back(stationData);  // Dodaj stację, jeśli jej jeszcze nie ma
}

// Zapisz zaktualizowaną bazę danych
std::ofstream outputFile(filePath);
if (outputFile.is_open()) {
try {
outputFile << dbData.dump(4); // Zapisz w formacie ładnie sformatowanego JSON
outputFile.close();
} catch (const std::exception& e) {
std::cerr << "Błąd podczas zapisywania do pliku: " << e.what() << "\n";
}
} else {
std::cerr << "Nie udało się otworzyć pliku do zapisu.\n";
}
}

void DatabaseManager::saveMeasurementData(string stationName, string sensorName, const std::vector<Measurement>& measurements) {
    std::string filename = "database.json";
    json db;

    if (fileExistsAndNotEmpty(filename)) {
        std::ifstream file(filename);
        db = json::parse(file);
    } else {
        db = json::array();  // lub json::object(), zależy od twojego formatu bazy
    }

    // dodaj dane pomiarowe do db…
    json entry;
    entry["stationName"] = stationName;
    entry["sensorName"] = sensorName;
    entry["measurements"] = json::array();
    for (const auto& m : measurements) {
        json mJson;
        mJson["date"] = m.getDate();
        mJson["value"] = m.getValue();
        entry["measurements"].push_back(mJson);
    }

    db.push_back(entry);

    std::cout << "Zapisana struktura JSON:\n" << db.dump(4) << std::endl;

    std::ofstream outFile(filename);
    outFile << db.dump(4);
}

std::vector<Station> DatabaseManager::loadFromDatabase(const std::string& filePath) {
    std::vector<Station> stations;

    // Sprawdzamy, czy plik istnieje i nie jest pusty
    if (!fileExistsAndNotEmpty(filePath)) {
        std::cerr << "Plik z danymi stacji nie istnieje lub jest pusty: " << filePath << std::endl;
        return stations; // Zwracamy pustą listę stacji
    }

    // Otwieramy plik
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << filePath << std::endl;
        return stations;
    }

    // Parsowanie danych JSON z pliku
    json db;
    file >> db;

    // Przechodzimy przez stacje i tworzymy obiekty Station
    for (const auto& entry : db) {
        int stationId = entry["stationId"];
        std::string stationName = entry["stationName"];
        std::string city = entry["city"];
        double latitude = entry["latitude"];   // Zakładając, że są dane o szerokości geograficznej
        double longitude = entry["longitude"]; // Zakładając, że są dane o długości geograficznej
        
        // Tworzymy obiekt Station
        Station station(stationId, stationName, city, latitude, longitude);
        stations.push_back(station);
    }

    return stations;
}

std::vector<Sensor> DatabaseManager::loadSensorDataFromDatabase(const std::string& filePath, int stationId) {
    std::vector<Sensor> sensors;

    // Sprawdzamy, czy plik istnieje i nie jest pusty
    if (!fileExistsAndNotEmpty(filePath)) {
        std::cerr << "Plik z danymi sensorów nie istnieje lub jest pusty: " << filePath << std::endl;
        return sensors; // Zwracamy pustą listę sensorów
    }

    // Otwieramy plik
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << filePath << std::endl;
        return sensors;
    }

    // Parsowanie danych JSON z pliku
    json db;
    file >> db;

    // Szukamy sensorów dla danej stacji
    for (const auto& entry : db) {
        int id = entry["stationId"];
        if (id == stationId) {
            for (const auto& sensorData : entry["sensors"]) {
                int sensorId = sensorData["sensorId"];
                std::string paramName = sensorData["paramName"];
                std::string paramFormula = sensorData["paramFormula"];  // Zakładając, że formuła jest w JSON
                std::string paramCode = sensorData["paramCode"];        // Zakładając, że kod parametru jest w JSON
                int idParam = sensorData["idParam"];                    // Zakładając, że id parametru jest w JSON
                
                // Tworzymy obiekt Sensor
                Sensor sensor(sensorId, id, paramName, paramFormula, paramCode, idParam);
                sensors.push_back(sensor);
            }
            break; // Po znalezieniu stacji, kończymy przeszukiwanie
        }
    }

    return sensors;
}

bool DatabaseManager::fileExistsAndNotEmpty(const std::string& filePath) {
    std::ifstream file(filePath);
    // Sprawdzamy, czy plik istnieje i jest otwarty
    if (!file.is_open()) {
        return false;
    }

    // Sprawdzamy, czy plik nie jest pusty
    file.seekg(0, std::ios::end);
    return file.tellg() > 0; // Jeśli rozmiar pliku > 0, to plik nie jest pusty
}