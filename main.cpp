// main.cpp

#include <iostream>
#include <vector>
#include "include/StationManager.h"
#include "ApiClient.h"
#include <locale>
#include <clocale>   // dla std::setlocale


int main() {
    StationManager stationManager;
    
    // Tworzymy wektor do przechowywania stacji
    std::vector<Station> stations;

    // Filtrowanie stacji po mieście "Warszawa"
    stationManager.loadStations(stations, "Warszawa");

    // Wypisujemy stacje z Warszawy
    std::cout << "Lista stacji w Warszawie:" << std::endl;
    for (const auto& station : stations) {
        std::cout << "ID: " << station.getId() << ", Name: " << station.getName()
                  << ", City: " << station.getCity() << ", Latitude: " 
                  << station.getLatitude() << ", Longitude: " << station.getLongitude() << std::endl;
    }

    // Teraz chcemy wyświetlić szczegóły jednej stacji (np. stacja o ID 1001)
    std::string stationId = "550";  // Zmienna stacji, którą chcemy wyświetlić
    ApiClient apiClient;
    try {
        nlohmann::json measurements = apiClient.getMeasurements(stationId);
        
        std::cout << "\nSzczegóły dla stacji o ID " << stationId << ":" << std::endl;
        std::cout << "Pomiary stacji: " << measurements.dump(4) << std::endl;  // Wypisuje dane w formie JSON

    } catch (const std::exception& e) {
        std::cerr << "Błąd podczas pobierania pomiarów: " << e.what() << std::endl;
    }

    return 0;
}
