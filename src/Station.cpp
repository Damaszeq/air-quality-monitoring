#include "Station.h"

Station::Station(int id, string name, double latitude, double longitude, string city,
                 string commune, string district, string province, vector<int> sensors)
    : id(id), name(name), latitude(latitude), longitude(longitude),
      city(city), commune(commune), district(district), province(province),
      sensorIDs(sensors) {}

int Station::getId() const { return id; }
string Station::getName() const { return name; }
double Station::getLatitude() const { return latitude; }
double Station::getLongitude() const { return longitude; }
string Station::getCity() const { return city; }
string Station::getCommune() const { return commune; }
string Station::getDistrict() const { return district; }
string Station::getProvince() const { return province; }
vector<int> Station::getSensorIDs() const { return sensorIDs; }

void Station::setId(int newId) { id = newId; }
void Station::setName(const string &newName) { name = newName; }
void Station::setLatitude(double newLatitude) { latitude = newLatitude; }
void Station::setLongitude(double newLongitude) { longitude = newLongitude; }
void Station::setCity(const string &newCity) { city = newCity; }
void Station::setCommune(const string &newCommune) { commune = newCommune; }
void Station::setDistrict(const string &newDistrict) { district = newDistrict; }
void Station::setProvince(const string &newProvince) { province = newProvince; }
void Station::setSensorIDs(const vector<int> &newSensors) { sensorIDs = newSensors; }

void Station::displayInfo() const {
    cout << "Stacja ID: " << id << endl;
    cout << "Nazwa: " << name << endl;
    cout << "Lokalizacja: " << latitude << ", " << longitude << endl;
    cout << "Miasto: " << city << ", Gmina: " << commune
         << ", Powiat: " << district << ", Województwo: " << province << endl;
    cout << "Czujniki: ";
    for (int sensor : sensorIDs)
        cout << sensor << " ";
    cout << endl;
}

bool Station::hasSensor(int sensorId) const {
    for (int sensor : sensorIDs) {
        if (sensor == sensorId)
            return true;
    }
    return false;
}
