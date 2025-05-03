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

    return 0;
}
