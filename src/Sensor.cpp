#include "Sensor.h"

Sensor::Sensor(int id, int stationId, const std::string& paramName,
               const std::string& paramFormula, const std::string& paramCode, int idParam)
    : id(id), stationId(stationId), paramName(paramName),
      paramFormula(paramFormula), paramCode(paramCode), idParam(idParam) {}

int Sensor::getId() const {
    return id;
}

int Sensor::getStationId() const {
    return stationId;
}

std::string Sensor::getParamName() const {
    return paramName;
}

std::string Sensor::getParamFormula() const {
    return paramFormula;
}

std::string Sensor::getParamCode() const {
    return paramCode;
}

int Sensor::getIdParam() const {
    return idParam;
}
