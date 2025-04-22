#include "Station.h"
#include <iostream>>

using namespace std;

Station::Station(int id, const string& name, const string& city, double latitude, double longitude)
    : id(id), name(name), city(city), latitude(latitude), longitude(longitude) {}

int Station::getId() const { return id; }
string Station::getName() const { return name; }
string Station::getCity() const { return city; }
double Station::getLatitude() const { return latitude; }
double Station::getLongitude() const { return longitude; }

void Station::setId(int newId) { id = newId; }
void Station::setName(const string& newName) { name = newName; }
void Station::setCity(const string& newCity) { city = newCity; }
void Station::setLatitude(double newLatitude) { latitude = newLatitude; }
void Station::setLongitude(double newLongitude) { longitude = newLongitude; }

void Station::displayInfo() const {
    cout << "Stacja ID: " << id << endl;
    cout << "Nazwa: " << name << endl;
    cout << "Miasto: " << city << ", Gmina: " << commune
         << ", Powiat: " << district << ", Województwo: " << province << endl;
    cout << "Położenie: " << latitude << ", " << longitude << endl;
    cout << "Czujniki: ";
    for (int sid : sensorIds) {
        cout << sid << " ";
    }
    cout << endl;
}

bool Station::hasSensor(int sensorId) const {
    for (int sid : sensorIds) {
        if (sid == sensorId) {
            return true;
        }
    }
    return false;
}