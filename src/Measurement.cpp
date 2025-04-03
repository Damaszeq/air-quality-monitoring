#include <iostream>
#include "Measurement.h"

using namespace std;

Measurement::Measurement(int id, int stationId, string paramName, string paramUnit, string date, double value)
    : id(id), stationId(stationId), pName(paramName), pUnit(paramUnit), date(date), value(value) {}

int Measurement::getId() const { return id; }
int Measurement::getStationId() const { return stationId; }
string Measurement::getPName() const { return pName; }
string Measurement::getPUnit() const { return pUnit; }
string Measurement::getDate() const { return date; }
double Measurement::getValue() const { return value; }

void Measurement::setId(int newId) { id = newId; }
void Measurement::setStationId(int newStationId) { stationId = newStationId; }
void Measurement::setPName(const string& newParamName) { pName = newParamName; }
void Measurement::setPUnit(const string& newParamUnit) { pUnit = newParamUnit; }
void Measurement::setDate(const string& newDate) { date = newDate; }
void Measurement::setValue(double newValue) { value = newValue; }
