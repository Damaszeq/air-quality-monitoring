#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Station {
private:
    int id;
    string name;
    double latitude;
    double longitude;
    string city;
    string commune;
    string district;
    string province;
    vector<int> sensorIDs;

public:
    // Konstruktor
    Station(int id, string name, double latitude, double longitude, string city,
            string commune, string district, string province, vector<int> sensors);

    // Gettery
    int getId() const;
    string getName() const;
    double getLatitude() const;
    double getLongitude() const;
    string getCity() const;
    string getCommune() const;
    string getDistrict() const;
    string getProvince() const;
    vector<int> getSensorIDs() const;

    // Settery
    void setId(int newId);
    void setName(const string &newName);
    void setLatitude(double newLatitude);
    void setLongitude(double newLongitude);
    void setCity(const string &newCity);
    void setCommune(const string &newCommune);
    void setDistrict(const string &newDistrict);
    void setProvince(const string &newProvince);
    void setSensorIDs(const vector<int> &newSensors);

    // Metoda do wyświetlania informacji o stacji
    void displayInfo() const;

    // Metoda sprawdzająca, czy stacja ma dany czujnik
    bool hasSensor(int sensorId) const;
};

#endif

