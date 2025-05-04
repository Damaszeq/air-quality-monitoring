#include "ApiClient.h"
#include <curl/curl.h>
#include <stdexcept>
#include <iostream>

ApiClient::ApiClient(const std::string& base_url) : base_url(base_url) {}

ApiClient::ApiClient() : base_url("https://api.gios.gov.pl/pjp-api/rest") {}

ApiClient::~ApiClient() {}

size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string ApiClient::makeRequest(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    // Inicjalizacja CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Ustawienie URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Włączenie weryfikacji SSL lub jej wyłączenie (zależnie od wymagań)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  // Wyłączanie weryfikacji SSL (można dostosować, jeśli potrzebujesz)

        // Ustawienie funkcji callback do zapisu odpowiedzi
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Wykonanie zapytania
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            // Błąd wykonania zapytania
            std::cerr << "CURL request failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            throw std::runtime_error("Failed to fetch data from API.");
        }

        // Zwolnienie zasobów
        curl_easy_cleanup(curl);
    } else {
        throw std::runtime_error("CURL initialization failed.");
    }

    // Zakończenie globalnej inicjalizacji CURL
    curl_global_cleanup();

    // Zwracamy wynik zapytania
    return readBuffer;
}

std::vector<nlohmann::json> ApiClient::getStations() {
    std::string url = "https://api.gios.gov.pl/pjp-api/rest/station/findAll";
    std::string response = makeRequest(url);
    return nlohmann::json::parse(response);
}

std::vector<nlohmann::json> ApiClient::getSensors(int stationId) {
    std::string url = base_url + "/station/sensors/" + std::to_string(stationId);
    std::string response = makeRequest(url);
    return nlohmann::json::parse(response);
}

std::vector<Measurement> ApiClient::getMeasurements(int sensorId) {
    std::string url = "https://api.gios.gov.pl/pjp-api/rest/data/getData/" + std::to_string(sensorId);
    std::string response = makeRequest(url);

    nlohmann::json jsonResponse = nlohmann::json::parse(response);

    // Sprawdzanie, czy "values" istnieje i czy nie jest puste
    if (jsonResponse.find("values") != jsonResponse.end() && !jsonResponse["values"].empty()) {
        std::vector<Measurement> measurements;
        
        for (const auto& value : jsonResponse["values"]) {
            if (value.contains("value") && !value["value"].is_null()) {
                // Dodanie pomiaru tylko wtedy, gdy wartość jest poprawna
                measurements.push_back(Measurement(value["date"], value["value"]));
            }
        }
        
        return measurements;
    } else {
        std::cerr << "Brak danych pomiarowych dla sensora: " << sensorId << std::endl;
        return {};  // Zwrócenie pustego wektora, gdy brak danych
    }
}

AirQualityIndex ApiClient::getAirQualityIndex(int stationId) {
    std::string url = base_url + "/aqindex/getIndex/" + std::to_string(stationId);
    std::string response = makeRequest(url);
    auto json = nlohmann::json::parse(response);

    auto parseIndexLevel = [](const nlohmann::json& obj) -> std::pair<int, std::string> {
        if (!obj.is_null() && obj.contains("id") && obj.contains("indexLevelName")) {
            return std::make_pair(obj["id"].get<int>(), obj["indexLevelName"].get<std::string>());
        }
        // Brak danych — zwracamy id = -1 i pusty string
        return std::make_pair(-1, "");
    };

    std::pair<int, std::string> stIndexLevel   = json.contains("stIndexLevel")   ? parseIndexLevel(json["stIndexLevel"])   : std::make_pair(-1, "");
    std::pair<int, std::string> so2IndexLevel  = json.contains("so2IndexLevel")  ? parseIndexLevel(json["so2IndexLevel"])  : std::make_pair(-1, "");
    std::pair<int, std::string> no2IndexLevel  = json.contains("no2IndexLevel")  ? parseIndexLevel(json["no2IndexLevel"])  : std::make_pair(-1, "");
    std::pair<int, std::string> pm10IndexLevel = json.contains("pm10IndexLevel") ? parseIndexLevel(json["pm10IndexLevel"]) : std::make_pair(-1, "");
    std::pair<int, std::string> pm25IndexLevel = json.contains("pm25IndexLevel") ? parseIndexLevel(json["pm25IndexLevel"]) : std::make_pair(-1, "");
    std::pair<int, std::string> o3IndexLevel   = json.contains("o3IndexLevel")   ? parseIndexLevel(json["o3IndexLevel"])   : std::make_pair(-1, "");

    std::string calcDate = "";
    if (json.contains("stCalcDate") && !json["stCalcDate"].is_null()) {
        calcDate = json["stCalcDate"].get<std::string>();
    }

    return AirQualityIndex(
        json["id"].get<int>(),
        calcDate,
        stIndexLevel.first, stIndexLevel.second,
        so2IndexLevel.first, so2IndexLevel.second,
        no2IndexLevel.first, no2IndexLevel.second,
        pm10IndexLevel.first, pm10IndexLevel.second,
        pm25IndexLevel.first, pm25IndexLevel.second,
        o3IndexLevel.first, o3IndexLevel.second
    );
}