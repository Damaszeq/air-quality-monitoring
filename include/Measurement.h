#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <string>

class Measurement {
public:
    friend class DatabaseManager;
    // Konstruktor z datą i wartością
    Measurement(const std::string& date, double value);

    // Konstruktor domyślny
    Measurement() : date(""), value(0.0f) {}

    // Gettery
    std::string getDate() const;
    double getValue() const;

private:
    std::string date;      // Data pomiaru
    double value;          // Wartość pomiaru
};

#endif // MEASUREMENT_H
