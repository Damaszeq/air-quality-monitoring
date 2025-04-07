#include "Database.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using namespace std;

Database::Database(const string& fileName) : fileName(fileName) {}


// ======================= POMIARY =======================

bool Database::saveMeasurements(const vector<Measurement>& measurements)
{
    json j;
    for (const auto& m : measurements)
    {
        j.push_back({
            {"id", m.getId()},
            {"stationId", m.getStationId()},
            {"pName", m.getPName()},
            {"pUnit", m.getPUnit()},
            {"date", m.getDate()},
            {"value", m.getValue()}
        });
    }

    ofstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Nie mozna otworzyc pliku do zapisu: " << fileName << endl;
        return false;
    }

    file << j.dump(4);
    file.close();
    return true;
}

vector<Measurement> Database::loadMeasurements()
{
    vector<Measurement> result;
    ifstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Nie mozna otworzyc pliku do odczytu: " << fileName << endl;
        return result;
    }

    json j;
    file >> j;
    for (const auto& el : j)
    {
        Measurement m(
            el.at("id"),
            el.at("stationId"),
            el.at("pName"),
            el.at("pUnit"),
            el.at("date"),
            el.at("value")
        );
        result.push_back(m);
    }
    measurements = result; // przechowujemy dane w klasie
    return result;
}

const vector<Measurement>& Database::getMeasurements() const
{
    return measurements;
}

void Database::addMeasurement(const Measurement& m)
{
    measurements.push_back(m);
}

vector<Measurement> Database::getMeasurementsByStationId(int stationId) const
{
    vector<Measurement> result;
    for (const auto& m : measurements)
    {
        if (m.getStationId() == stationId)
        {
            result.push_back(m);
        }
    }
    return result;
}

// ======================= STACJE =======================

bool Database::saveStations(const vector<Station>& stations)
{
    json j;
    for (const auto& s : stations)
    {
        j.push_back({
            {"id", s.getId()},
            {"name", s.getName()},
            {"city", s.getCity()},
            {"latitude", s.getLatitude()},
            {"longitude", s.getLongitude()}
        });
    }

    ofstream file("stations.json");
    if (!file.is_open())
    {
        cerr << "Nie mozna otworzyc pliku do zapisu stacji!" << endl;
        return false;
    }

    file << j.dump(4);
    file.close();
    return true;
}

vector<Station> Database::loadStations()
{
    vector<Station> result;
    ifstream file("stations.json");
    if (!file.is_open())
    {
        cerr << "Nie mozna otworzyc pliku do odczytu stacji!" << endl;
        return result;
    }

    json j;
    file >> j;
    for (const auto& el : j)
    {
        Station s(
            el.at("id"),
            el.at("name"),
            el.at("city"),
            el.at("latitude"),
            el.at("longitude")
        );
        result.push_back(s);
    }
    stations = result;
    return result;
}

const vector<Station>& Database::getStations() const
{
    return stations;
}

void Database::addStation(const Station& s)
{
    stations.push_back(s);
}
