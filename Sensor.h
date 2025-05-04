#ifndef SENSOR_H
#define SENSOR_H

#include <string>

class Sensor {
private:
    int id;
    int stationId;
    std::string paramName;
    std::string paramFormula;
    std::string paramCode;
    int idParam;

public:
    Sensor(int id, int stationId, const std::string& paramName,
           const std::string& paramFormula, const std::string& paramCode, int idParam);

    int getId() const;
    int getStationId() const;
    std::string getParamName() const;
    std::string getParamFormula() const;
    std::string getParamCode() const;
    int getIdParam() const;
};

#endif // SENSOR_H
