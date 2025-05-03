// include/UiHelper.h
#ifndef UIHELPER_H
#define UIHELPER_H

#include <string>
#include <vector>
#include "Station.h"
#include "Sensor.h"
#include "Measurement.h"

class UiHelper {
public:
    friend class Measurement;
    /// Pyta o nazwę miasta (może być puste) i zwraca ją.
    static std::string askCity();

    /// Wyświetla listę stacji dla podanego miasta.
    static void displayStations(const std::vector<Station>& stations, const std::string& city);

    /// Pyta o współrzędne i promień (w km).
    static void askLocationAndRadius(double &latitude, double &longitude, double &radiusKm);

    /// Znajduje i wyświetla najbliższą stację spośród wektora.
    static void displayNearestStation(const std::vector<Station>& stations,
                                      double latitude, double longitude);
    static void displaySensors(const std::vector<Sensor>& sensors);

    static void displaySensorData(const std::vector<Measurement>& data);

    static int askStationId();

    static int askSensorId();
};

#endif // UIHELPER_H
