#ifndef STATION_H
#define STATION_H

#include <string>

using namespace std;

class Station
{
private:
    int id;
    string name;
    string city;
    double latitude;
    double longitude;

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
};

#endif // STATION_H
