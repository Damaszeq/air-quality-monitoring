// src/UiHelper.cpp
#include "UiHelper.h"
#include <iostream>
#include <cmath>
#include <limits>
const double M_PI = 3.14;
// Zamienia stopnie na radiany
static double deg2rad(double deg) {
    return deg * M_PI / 180.0;
}

// Oblicza odległość Haversine (w km) między punktem 1 i 2
static double haversine(double lat1, double lon1, double lat2, double lon2) {
    constexpr double R = 6371.0; // promień Ziemi w km
    double dLat = deg2rad(lat2 - lat1);
    double dLon = deg2rad(lon2 - lon1);
    double a = std::sin(dLat/2) * std::sin(dLat/2)
             + std::cos(deg2rad(lat1)) * std::cos(deg2rad(lat2))
             * std::sin(dLon/2) * std::sin(dLon/2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    return R * c;
}

// ————— Definicje metod UiHelper —————

std::string UiHelper::askCity() {
    std::cout << "Podaj nazwę miasta (lub zostaw puste, aby wyświetlić wszystkie stacje): ";
    std::string city;
    // Użycie getline, aby obsłużyć również puste wejście
    std::getline(std::cin, city);
    return city;
}

void UiHelper::displayStations(const std::vector<Station>& stations, const std::string& city) {
    if (stations.empty()) {
        std::cout << "Brak stacji dla miasta \"" << city << "\" lub brak danych.\n";
        return;
    }
    std::cout << "Lista stacji";
    if (!city.empty()) std::cout << " w " << city;
    std::cout << ":\n";
    for (const auto& s : stations) {
        std::cout 
            << "ID: "       << s.getId()
            << ", Name: "   << s.getName()
            << ", City: "   << s.getCity()
            << ", Lat: "    << s.getLatitude()
            << ", Lon: "    << s.getLongitude()
            << "\n";
    }
}

void UiHelper::displaySensors(const std::vector<Sensor>& sensors) {
    if (sensors.empty()) {
        std::cout << "Brak sensorów dla tej stacji.\n";
        return;
    }

    std::cout << "Dostępne sensory dla wybranej stacji:\n";
    std::cout << "-------------------------------------\n";

    for (const auto& sensor : sensors) {
        std::cout << "ID sensora: " << sensor.getId() << "\n";
        std::cout << "Parametr:   " << sensor.getParamName() << "\n";
        std::cout << "Wzór:       " << sensor.getParamFormula() << "\n";
        std::cout << "Kod:        " << sensor.getParamCode() << "\n";
        std::cout << "-------------------------------------\n";
    }
}

int UiHelper::askStationId() {
    int stationId;
    std::cout << "Podaj ID stacji pomiarowej: ";
    std::cin >> stationId;
    return stationId;
}

void UiHelper::askLocationAndRadius(double &latitude, double &longitude, double &radiusKm) {
    std::cout << "Podaj szerokość geograficzną: ";
    std::cin >> latitude;
    std::cout << "Podaj długość geograficzną: ";
    std::cin >> longitude;
    std::cout << "Podaj promień (km): ";
    std::cin >> radiusKm;
    // po std::cin zostaje '\n' w buforze
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void UiHelper::displayNearestStation(const std::vector<Station>& stations,
                                     double latitude, double longitude) {
    if (stations.empty()) {
        std::cout << "Brak stacji do wyszukania.\n";
        return;
    }
    // Szukamy minimalnej odległości
    double bestDist = std::numeric_limits<double>::infinity();
    const Station* bestStation = nullptr;

    for (const auto& s : stations) {
        double d = haversine(latitude, longitude, s.getLatitude(), s.getLongitude());
        if (d < bestDist) {
            bestDist = d;
            bestStation = &s;
        }
    }

    if (bestStation) {
        std::cout << "Najbliższa stacja (odległość " << bestDist << " km):\n"
                  << "ID: "     << bestStation->getId()
                  << ", Name: " << bestStation->getName()
                  << ", City: " << bestStation->getCity()
                  << ", Lat: "  << bestStation->getLatitude()
                  << ", Lon: "  << bestStation->getLongitude()
                  << "\n";
    }
}
