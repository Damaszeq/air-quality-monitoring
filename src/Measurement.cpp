#include "Measurement.h"

// Konstruktor z wartościami
Measurement::Measurement(const std::string& date, double value)
    : date(date), value(value) {}

// Funkcja do zwracania daty
std::string Measurement::getDate() const {
    return date;
}

// Funkcja do zwracania wartości pomiaru
double Measurement::getValue() const {
    return value;
}
