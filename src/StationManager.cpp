#include "StationManager.h"
#include "ApiClient.h" // Zakładając, że masz klasę ApiClient odpowiedzialną za pobieranie danych z API
#include <iostream>
#include <nlohmann/json.hpp>

const double M_PI = 3.1415;

// Konstruktor
StationManager::StationManager() {}

// Funkcja ładująca stacje z API
void StationManager::loadStations( const std::string& cityFilter) {
    ApiClient apiClient;
    stations.clear();
    try {
        // Pobranie stacji z API
        std::vector<nlohmann::json> stationsJson = apiClient.getStations();

        // Zamiana danych z JSON na obiekty Station
        for (const auto& stationData : stationsJson) {
            int id = stationData["id"];
            std::string name = stationData["stationName"];

            std::string city;
            if (stationData["city"].is_object()) {
                city = stationData["city"]["name"];
            }

            // Dodaj stację tylko jeśli pasuje do filtra miasta
            if (cityFilter.empty() || city == cityFilter) {
                double latitude = 0.0;
                double longitude = 0.0;

                if (stationData["gegrLat"].is_string()) {
                    try {
                        latitude = std::stod(stationData["gegrLat"].get<std::string>());
                    } catch (const std::invalid_argument&) {
                        std::cerr << "Błąd: gegrLat nie jest poprawnym tekstem do konwersji na liczbę!" << std::endl;
                    } catch (const std::out_of_range&) {
                        std::cerr << "Błąd: gegrLat jest poza zakresem dla typu double!" << std::endl;
                    }
                }

                if (stationData["gegrLon"].is_string()) {
                    try {
                        longitude = std::stod(stationData["gegrLon"].get<std::string>());
                    } catch (const std::invalid_argument&) {
                        std::cerr << "Błąd: gegrLon nie jest poprawnym tekstem do konwersji na liczbę!" << std::endl;
                    } catch (const std::out_of_range&) {
                        std::cerr << "Błąd: gegrLon jest poza zakresem dla typu double!" << std::endl;
                    }
                }

                // Tworzymy obiekt stacji i dodajemy go do wektora
                Station station(id, name, city, latitude, longitude);
                stations.push_back(station);
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Błąd podczas pobierania danych: " << e.what() << std::endl;
    }
}

// Funkcja zwracająca wszystkie stacje
std::vector<Station> StationManager::getAllStations() {
    return stations;
}

std::vector<Sensor> StationManager::getSensorsForStation(int stationId) {
    std::vector<Sensor> sensors;
    ApiClient apiClient;
    sensors.clear();
    // Pobierz dane JSON o sensorach z API
    auto jsonSensors = apiClient.getSensors(stationId);

    for (const auto& jsonSensor : jsonSensors) {
        int id = jsonSensor.at("id").get<int>();
        int stationId = jsonSensor.at("stationId").get<int>();

        std::string paramName = jsonSensor.at("param").at("paramName").get<std::string>();
        std::string paramFormula = jsonSensor.at("param").at("paramFormula").get<std::string>();
        std::string paramCode = jsonSensor.at("param").at("paramCode").get<std::string>();
        int paramId = jsonSensor.at("param").at("idParam").get<int>();

        Sensor sensor(id, stationId, paramName, paramFormula, paramCode, paramId);
        sensors.push_back(sensor);
    }

    return sensors;
}

// Funkcja pomocnicza do obliczenia odległości Haversine
 double haversine(double lat1, double lon1, double lat2, double lon2) {
    constexpr double R = 6371.0; // promień Ziemi w kilometrach

    double latRad1 = lat1 * M_PI / 180.0;
    double latRad2 = lat2 * M_PI / 180.0;
    double deltaLat = (lat2 - lat1) * M_PI / 180.0;
    double deltaLon = (lon2 - lon1) * M_PI / 180.0;

    double a = sin(deltaLat / 2) * sin(deltaLat / 2) +
               cos(latRad1) * cos(latRad2) *
               sin(deltaLon / 2) * sin(deltaLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R * c;
}

// Funkcja zwracająca stacje w promieniu od danej lokalizacji
std::vector<Station> StationManager::getStationsWithinRadius(double latitude, double longitude, double radiusKm) const {
    std::vector<Station> nearbyStations;
    for (const auto& station : stations) {
        double distance = haversine(latitude, longitude, station.getLatitude(), station.getLongitude());
        if (distance <= radiusKm) {
            nearbyStations.push_back(station);
        }
    }
    return nearbyStations;
}


