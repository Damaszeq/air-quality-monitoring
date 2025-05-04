#include "AirQualityIndex.h"

// Konstruktor klasy AirQualityIndex
AirQualityIndex::AirQualityIndex(int stationId,
                                 const std::string& calcDate,
                                 int stIndexId, const std::string& stIndexName,
                                 int so2IndexId, const std::string& so2IndexName,
                                 int no2IndexId, const std::string& no2IndexName,
                                 int pm10IndexId, const std::string& pm10IndexName,
                                 int pm25IndexId, const std::string& pm25IndexName,
                                 int o3IndexId, const std::string& o3IndexName)
    : stationId(stationId), calcDate(calcDate),
      stIndexId(stIndexId), stIndexName(stIndexName),
      so2IndexId(so2IndexId), so2IndexName(so2IndexName),
      no2IndexId(no2IndexId), no2IndexName(no2IndexName),
      pm10IndexId(pm10IndexId), pm10IndexName(pm10IndexName),
      pm25IndexId(pm25IndexId), pm25IndexName(pm25IndexName),
      o3IndexId(o3IndexId), o3IndexName(o3IndexName) {}

// Gettery
int AirQualityIndex::getStationId() const {
    return stationId;
}

std::string AirQualityIndex::getCalcDate() const {
    return calcDate;
}

int AirQualityIndex::getStIndexId() const {
    return stIndexId;
}

std::string AirQualityIndex::getStIndexName() const {
    return stIndexName;
}

int AirQualityIndex::getSo2IndexId() const {
    return so2IndexId;
}

std::string AirQualityIndex::getSo2IndexName() const {
    return so2IndexName;
}

int AirQualityIndex::getNo2IndexId() const {
    return no2IndexId;
}

std::string AirQualityIndex::getNo2IndexName() const {
    return no2IndexName;
}

int AirQualityIndex::getPm10IndexId() const {
    return pm10IndexId;
}

std::string AirQualityIndex::getPm10IndexName() const {
    return pm10IndexName;
}

int AirQualityIndex::getPm25IndexId() const {
    return pm25IndexId;
}

std::string AirQualityIndex::getPm25IndexName() const {
    return pm25IndexName;
}

int AirQualityIndex::getO3IndexId() const {
    return o3IndexId;
}

std::string AirQualityIndex::getO3IndexName() const {
    return o3IndexName;
}

// Metody pomocnicze zwracające pełną wartość wskaźnika
std::string AirQualityIndex::getStIndex() const {
    return std::to_string(stIndexId) + " - " + stIndexName;
}

std::string AirQualityIndex::getSo2Index() const {
    return std::to_string(so2IndexId) + " - " + so2IndexName;
}

std::string AirQualityIndex::getNo2Index() const {
    return std::to_string(no2IndexId) + " - " + no2IndexName;
}

std::string AirQualityIndex::getPm10Index() const {
    return std::to_string(pm10IndexId) + " - " + pm10IndexName;
}

std::string AirQualityIndex::getPm25Index() const {
    return std::to_string(pm25IndexId) + " - " + pm25IndexName;
}

std::string AirQualityIndex::getO3Index() const {
    return std::to_string(o3IndexId) + " - " + o3IndexName;
}
