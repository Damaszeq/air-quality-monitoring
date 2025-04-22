#include <iostream>
#include <vector>
#include "include\Station.h"
#include "include\ApiClient.h"

using namespace std;

int main() {
    // Bazowy URL API
    std::string base_url = "https://powietrze.gios.gov.pl/pjp/api";
    ApiClient apiClient(base_url);

    try {
        // Pobranie listy stacji
        auto stations = apiClient.getStations();
        std::cout << "Stacje: " << std::endl;
        for (const auto& station : stations) {
            std::cout << "ID: " << station["id"] << ", Nazwa: " << station["stationName"] << std::endl;
        }

        // Pobranie danych o pomiarach dla konkretnej stacji (przykład dla ID = 1)
        std::string stationId = "1";
        auto measurements = apiClient.getMeasurements(stationId);
        std::cout << "Pomiar dla stacji " << stationId << ": " << measurements.dump(4) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Błąd: " << e.what() << std::endl;
    }

    return 0;
}






