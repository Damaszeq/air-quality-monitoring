#ifndef APICLIENT_H
#define APICLIENT_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

// Klasa reprezentująca klienta API
class ApiClient {
public:
    ApiClient(const std::string& base_url);
    ~ApiClient();

    // Funkcja do pobierania danych o stacjach
    std::vector<nlohmann::json> getStations();

    // Funkcja do pobierania danych o pomiarach
    nlohmann::json getMeasurements(const std::string& stationId);

private:
    std::string base_url;
    std::string makeRequest(const std::string& url);
};

#endif // APICLIENT_H
