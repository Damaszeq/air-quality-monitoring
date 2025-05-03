// include/UiHelper.h
#ifndef UIHELPER_H
#define UIHELPER_H

#include <string>
#include <vector>
#include "Station.h"

class UiHelper {
public:
    /// Pyta o nazwę miasta (może być puste) i zwraca ją.
    static std::string askCity();

    /// Wyświetla listę stacji dla podanego miasta.
    static void displayStations(const std::vector<Station>& stations, const std::string& city);

    /// Pyta o współrzędne i promień (w km).
    static void askLocationAndRadius(double &latitude, double &longitude, double &radiusKm);

    /// Znajduje i wyświetla najbliższą stację spośród wektora.
    static void displayNearestStation(const std::vector<Station>& stations,
                                      double latitude, double longitude);
};

#endif // UIHELPER_H
