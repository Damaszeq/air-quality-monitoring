// src/UiHelper.cpp
#include "UiHelper.h"
#include <iostream>
#include <algorithm>
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
    std::string city;
    std::cout << "Podaj nazwę miejscowości: ";
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

void UiHelper::displaySensors(const std::vector<Sensor>& sensors, const Station& station) {
    // Zamiast standardowego tekstu wyświetl adres stacji
    std::cout << "Sensory dla stacji: " << station.getName() << std::endl;
    std::cout << "-------------------------------------\n";

    for (const auto& sensor : sensors) {
        std::cout << "ID sensora: " << sensor.getId() << std::endl;
        std::cout << "Parametr:   " << sensor.getParamName() << std::endl;  // Wywołanie getParamName() zamiast getParameter()
        std::cout << "Wzór:       " << sensor.getParamFormula() << std::endl;  // Wywołanie getParamFormula() zamiast getFormula()
        std::cout << "Kod:        " << sensor.getParamCode() << std::endl;     // Wywołanie getParamCode() zamiast getCode()
        std::cout << "-------------------------------------\n";
    }
}



void UiHelper::displaySensorData(const std::vector<Measurement>& measurements) {
    if (measurements.empty()) {
        std::cout << "Brak dostępnych danych pomiarowych." << std::endl;
        return;
    }

    for (const auto& measurement : measurements) {
        std::cout << "Data: " << measurement.date << ", Wartość: " << measurement.value << std::endl;
    }
}

int UiHelper::askSensorId() {
    int sensorId;
    std::cout << "Podaj ID sensora: ";
    std::cin >> sensorId;
    return sensorId;
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

const Station* UiHelper::selectStationById(const std::vector<Station>& stations) {
    int id = askStationId();

    for (const auto& s : stations) {
        if (s.getId() == id) {
            return &s;
        }
    }

    std::cout << "Stacja o podanym ID nie istnieje na liście. Spróbuj ponownie.\n";
    return nullptr;
}

int UiHelper::askStationId() {
    std::cout << "Podaj ID stacji: ";
    int id;
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Wyczyść bufor
    return id;
}



const Sensor* UiHelper::selectSensorById(const std::vector<Sensor>& sensors, const Station& station) {
    while (true) {
        std::cout << "Podaj ID sensora: ";
        int id;
        std::cin >> id;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        auto it = std::find_if(sensors.begin(), sensors.end(),
                               [id](const Sensor& s) { return s.getId() == id; });

        if (it != sensors.end()) {
            return &(*it);
        } else {
            std::cout << "Sensor o podanym ID nie istnieje na liście. Spróbuj ponownie.\n";
            // NIE wywołujemy ponownie displaySensors tutaj!
        }
    }
}



bool UiHelper::confirmAction(const std::string& message) {
    std::cout << message << " (y/n): ";
    char response;
    std::cin >> response;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return (response == 'y' || response == 'Y');
}

void UiHelper::displayAirQualityIndex(const AirQualityIndex& airQualityIndex) {
    std::cout << "Indeks jakości powietrza dla stacji: " << airQualityIndex.getStationId() << std::endl;
    std::cout << "Data obliczenia: " << airQualityIndex.getCalcDate() << std::endl;

    bool hasData = false; // Flaga do sprawdzenia, czy mamy jakiekolwiek dane do wyświetlenia

    // St Index
    if (airQualityIndex.getStIndexId() != -1) {
        std::cout << "Indeks St: " << airQualityIndex.getStIndexName() 
                  << std::endl;
        hasData = true;
    }

    // SO2 Index
    if (airQualityIndex.getSo2IndexId() != -1) {
        std::cout << "Indeks SO2: " << airQualityIndex.getSo2IndexName() 
                  << std::endl;
        hasData = true;
    }

    // NO2 Index
    if (airQualityIndex.getNo2IndexId() != -1) {
        std::cout << "Indeks NO2: " << airQualityIndex.getNo2IndexName() 
                  << std::endl;
        hasData = true;
    }

    // PM10 Index
    if (airQualityIndex.getPm10IndexId() != -1) {
        std::cout << "Indeks PM10: " << airQualityIndex.getPm10IndexName() 
                  << std::endl;
        hasData = true;
    }

    // PM2.5 Index
    if (airQualityIndex.getPm25IndexId() != -1) {
        std::cout << "Indeks PM2.5: " << airQualityIndex.getPm25IndexName() 
                  << std::endl;
        hasData = true;
    }

    // O3 Index
    if (airQualityIndex.getO3IndexId() != -1) {
        std::cout << "Indeks O3: " << airQualityIndex.getO3IndexName() 
                  << std::endl;
        hasData = true;
    }

    // Jeśli nie ma żadnych danych, wyświetl komunikat "Brak danych"
    if (!hasData) {
        std::cout << "Brak danych o jakości powietrza.\n";
    }
}


int UiHelper::askStationId(const std::vector<Station>& stations, const std::string& city) {
    int stationId;
    bool validId = false;

    while (!validId) {
        std::cout << "Podaj ID stacji: ";
        std::cin >> stationId;

        bool foundValidStation = false;
        for (const auto& station : stations) {
            if (station.getId() == stationId) {
                if (station.getCity() == city) {
                    foundValidStation = true;
                    validId = true;
                    break;
                } else {
                    std::cout << "To ID stacji należy do innej miejscowości: " << station.getCity() << ".\n";
                    std::cout << "Czy chcesz wybrać inną miejscowość? (t/n): ";
                    char choice;
                    std::cin >> choice;
                    if (choice == 't' || choice == 'T') {
                        return -1;  // użytkownik chce zmienić miasto
                    } else {
                        validId = false;
                    }
                    break;
                }
            }
        }

        if (!foundValidStation) {
            std::cout << "Stacja o podanym ID nie istnieje w tej miejscowości. Spróbuj ponownie.\n";
        }
    }

    return stationId;
}

bool UiHelper::askSaveToDatabase() {
    std::cout << "Czy chcesz zapisać dane do lokalnej bazy danych? (T/N): ";
    std::string choice;
    std::getline(std::cin, choice);
    return (choice == "T" || choice == "t");
}

