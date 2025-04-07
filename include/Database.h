#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include "Measurement.h"
#include "Station.h"

using namespace std;

class Database
{
private:
    string fileName;
    vector<Measurement> measurements;
    vector<Station> stations;

public:
    // Konstruktor
    Database(const string& fileName);

    // Pomiar
    bool saveMeasurements(const vector<Measurement>& measurements);
    vector<Measurement> loadMeasurements();
    const vector<Measurement>& getMeasurements() const;
    void addMeasurement(const Measurement& m);
    vector<Measurement> getMeasurementsByStationId(int stationId) const;

    // Stacje
    bool saveStations(const vector<Station>& stations);
    vector<Station> loadStations();
    const vector<Station>& getStations() const;
    void addStation(const Station& s);
};

#endif // DATABASE_H
