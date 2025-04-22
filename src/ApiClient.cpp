#include "ApiClient.h"
#include <curl/curl.h>
#include <stdexcept>
#include <iostream>

ApiClient::ApiClient(const std::string& base_url) : base_url(base_url) {}

ApiClient::~ApiClient() {}

size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string ApiClient::makeRequest(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
   
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "CURL request failed: " << curl_easy_strerror(res) << std::endl;
            throw std::runtime_error("Failed to fetch data from API.");
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return readBuffer;
}

std::vector<nlohmann::json> ApiClient::getStations() {
    std::string url = base_url + "/station/list";
    std::string response = makeRequest(url);
    return nlohmann::json::parse(response);
}

nlohmann::json ApiClient::getMeasurements(const std::string& stationId) {
    std::string url = base_url + "/measurement/" + stationId;
    std::string response = makeRequest(url);
    return nlohmann::json::parse(response);
}
