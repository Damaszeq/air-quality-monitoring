#ifndef APICLIENT_H
#define APICLIENT_H

#include <string>
#include <vector>
#include <Measurement.h>
#include <AirQualityIndex.h>
#include <nlohmann/json.hpp>

// Klasa reprezentująca klienta API
class ApiClient {
public:
    ApiClient(const std::string& base_url);
    ApiClient();
    ~ApiClient();

    friend class Measurement;

    // Funkcja do pobierania danych o stacjach
    std::vector<nlohmann::json> getStations();

    // Funkcja do pobierania danych o sensorach danej stacji
     std::vector<nlohmann::json> getSensors(int stationId);

     AirQualityIndex getAirQualityIndex(int stationId);

    // Funkcja do pobierania danych sensora
     std::vector<Measurement> getMeasurements(int sensorId);
private:
    std::string base_url;
    std::string makeRequest(const std::string& url);
};

#endif // APICLIENT_H
