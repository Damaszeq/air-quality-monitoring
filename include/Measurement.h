#ifndef MEASUREMENT_H
#define MEASUREMENT_H
#include <string>

using namespace std;

class Measurement
{
private:
    int id;  
    int stationId; 
    string pName; 
    string pUnit; 
    string date; 
    double value;  

public:
    // Konstruktor
    Measurement(int id, int stationId, string pName, string pUnit, string date, double value);

    // Gettery
    int getId() const;
    int getStationId() const;
    string getPName() const;
    string getPUnit() const;
    string getDate() const;
    double getValue() const;

    // Settery
    void setId(int newId);
    void setStationId(int newStationId);
    void setPName(const string& newPName);
    void setPUnit(const string& newPUnit);
    void setDate(const string& newDate);
    void setValue(double newValue);
};

#endif // MEASUREMENT_H
