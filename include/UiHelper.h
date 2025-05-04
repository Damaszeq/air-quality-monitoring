// include/UiHelper.h
#ifndef UIHELPER_H
#define UIHELPER_H

#include <string>
#include <vector>
#include "Station.h"
#include "Sensor.h"
#include "Measurement.h"
#include "AirQualityIndex.h"


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
    static void displaySensors(const std::vector<Sensor>& sensors, const Station& station);

    static void displaySensorData(const std::vector<Measurement>& data);

    static int askStationId(const std::vector<Station>& stations, const std::string& city);

    // Deklaracja (bez argumentów)
    static int askStationId();
    static bool askSaveToDatabase();
    static int askSensorId();

    static const Station* selectStationById(const std::vector<Station>& stations);
    static const Sensor* selectSensorById(const std::vector<Sensor>& sensors, const Station& station);
    static bool confirmAction(const std::string& message);

    static void displayAirQualityIndex(const AirQualityIndex& aqi);

};

#endif // UIHELPER_H
