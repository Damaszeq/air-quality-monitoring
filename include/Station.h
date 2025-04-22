#ifndef STATION_H
#define STATION_H

#include <string>
#include <vector>

using namespace std;

class Station
{
private:
int id;
string name;
double latitude;
double longitude;
string city;
string commune;
string district;
string province;
vector<int> sensorIds;

public:
    // Konstruktor
    Station(int id, const string& name, const string& city, double latitude, double longitude);

    // Gettery
    int getId() const;
    string getName() const;
    string getCity() const;
    double getLatitude() const;
    double getLongitude() const;

    // Settery
    void setId(int newId);
    void setName(const string& newName);
    void setCity(const string& newCity);
    void setLatitude(double newLatitude);
    void setLongitude(double newLongitude);

    //Metody
    void displayInfo() const;
    bool hasSensor(int sensorId) const;
};

#endif // STATION_H
