#include <iostream>
#include <vector>
#include "StationManager.h"
#include "ApiClient.h"
#include <locale>
#include "UiHelper.h"
#include <clocale>   // dla std::setlocale

int main() {
    StationManager manager;

    std::string city = UiHelper::askCity();
    manager.loadStations(city);   // <<<<< Ładujemy bezpośrednio do managera (nie do allStations)

    const std::vector<Station>& stations = manager.getAllStations();
    UiHelper::displayStations(stations, city);

    int stationId = UiHelper::askStationId();  // Zapytanie o ID stacji
    std::vector<Sensor> sensors = manager.getSensorsForStation(stationId);  // Pobranie sensorów
    UiHelper::displaySensors(sensors);  // Wyświetlenie sensorów

    int sensorId = UiHelper::askSensorId();  // Funkcja do zapytania o ID sensora

    // Pobranie danych pomiarowych dla wybranego sensora
    ApiClient apiClient;
    std::vector<Measurement> measurements = apiClient.getMeasurements(sensorId);

    // Wyświetlenie danych pomiarowych
    UiHelper::displaySensorData(measurements);
    
    return 0;
}
