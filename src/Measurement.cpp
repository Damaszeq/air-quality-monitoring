#include <iostream>
#include "Measurement.h"

using namespace std;

Measurement::Measurement(const std::string& date, double value)
    : date(date), value(value) {}

std::string Measurement::getDate() const {
    return date;
}

double Measurement::getValue() const {
    return value;
}