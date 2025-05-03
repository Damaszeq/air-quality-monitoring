#ifndef STATIONMANAGER_H
#define STATIONMANAGER_H

#include <vector>
#include <string>
#include "Station.h" // Zakładając, że klasa Station jest zdefiniowana w tym pliku

class StationManager {
private:
    std::vector<Station> stations; // Lista stacji

public:
    // Konstruktor
    StationManager();

    // Funkcja zwracająca wszystkie stacje
    std::vector<Station> getAllStations();

    // Funkcja zwracająca stacje w danym mieście
    const std::vector<Station>& getStationsByCity(const std::string& cityFilter) const;

    // Funkcja zwracająca stacje w promieniu od danej lokalizacji
    std::vector<Station> getStationsWithinRadius(double latitude, double longitude, double radiusKm) const;

    // Funkcja ładująca stacje, pozostaje bez zmian
    void loadStations(const std::string& cityFilter = "");
    
    // Funkcja pomocnicza do obliczania odległości między dwoma punktami (lat, lon)
    double calculateDistance(double lat1, double lon1, double lat2, double lon2);
};

#endif // STATIONMANAGER_H
