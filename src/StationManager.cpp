#include "StationManager.h"
#include "ApiClient.h" // Zakładając, że masz klasę ApiClient odpowiedzialną za pobieranie danych z API
#include <iostream>
#include <nlohmann/json.hpp>

const double M_PI = 3.1415;

// Konstruktor
StationManager::StationManager() {}

// Funkcja ładująca stacje z API
void StationManager::loadStations(std::vector<Station>& stations, const std::string& cityFilter) {
    ApiClient apiClient;

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

// Funkcja zwracająca stacje w danym mieście
std::vector<Station> StationManager::getStationsByCity(const std::string& city) {
    std::vector<Station> filteredStations;
    for (const auto& station : stations) {
        if (station.getCity() == city) {
            filteredStations.push_back(station);
        }
    }
    return filteredStations;
}

// Funkcja zwracająca stacje w promieniu od danej lokalizacji
std::vector<Station> StationManager::getStationsInRadius(double lat, double lon, double radius_km) {
    std::vector<Station> filteredStations;
    for (const auto& station : stations) {
        double distance = calculateDistance(lat, lon, station.getLatitude(), station.getLongitude());
        if (distance <= radius_km) {
            filteredStations.push_back(station);
        }
    }
    return filteredStations;
}

// Funkcja pomocnicza do obliczania odległości między dwoma punktami (lat, lon)
double StationManager::calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    const double earthRadius = 6371.0; // Promień Ziemi w kilometrach

    // Obliczanie różnic w radianach
    double lat1Rad = lat1 * M_PI / 180.0;
    double lon1Rad = lon1 * M_PI / 180.0;
    double lat2Rad = lat2 * M_PI / 180.0;
    double lon2Rad = lon2 * M_PI / 180.0;

    // Obliczanie różnicy między współrzędnymi
    double deltaLat = lat2Rad - lat1Rad;
    double deltaLon = lon2Rad - lon1Rad;

    // Obliczanie odległości Haversine'a
    double a = std::sin(deltaLat / 2) * std::sin(deltaLat / 2) +
               std::cos(lat1Rad) * std::cos(lat2Rad) *
               std::sin(deltaLon / 2) * std::sin(deltaLon / 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    // Odległość w kilometrach
    return earthRadius * c;
}
