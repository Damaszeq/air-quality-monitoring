#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <string>

class Measurement {
public:
    Measurement(const std::string& date, double value);
    Measurement() : date(""), value(0.0f) {}
    // Gettery
    std::string getDate() const;
    double getValue() const;

    std::string date;  // Data pomiaru
    double value;      // Wartość pomiaru
};

#endif // MEASUREMENT_H
