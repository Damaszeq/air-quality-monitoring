#include "StationManager.h"
#include <iostream>
#include <nlohmann/json.hpp>

void loadStations(std::vector<Station>& stations, const std::string& cityFilter) {
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
