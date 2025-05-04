#ifndef AIR_QUALITY_INDEX_H
#define AIR_QUALITY_INDEX_H

#include <string>

class AirQualityIndex {
private:
    int stationId;
    std::string calcDate;

    int stIndexId;
    std::string stIndexName;

    int so2IndexId;
    std::string so2IndexName;

    int no2IndexId;
    std::string no2IndexName;

    int pm10IndexId;
    std::string pm10IndexName;

    int pm25IndexId;
    std::string pm25IndexName;

    int o3IndexId;
    std::string o3IndexName;

public:
    AirQualityIndex(int stationId,
                    const std::string& calcDate,
                    int stIndexId, const std::string& stIndexName,
                    int so2IndexId, const std::string& so2IndexName,
                    int no2IndexId, const std::string& no2IndexName,
                    int pm10IndexId, const std::string& pm10IndexName,
                    int pm25IndexId, const std::string& pm25IndexName,
                    int o3IndexId, const std::string& o3IndexName);

    int getStationId() const;
    std::string getCalcDate() const;

    int getStIndexId() const;
    std::string getStIndexName() const;

    int getSo2IndexId() const;
    std::string getSo2IndexName() const;

    int getNo2IndexId() const;
    std::string getNo2IndexName() const;

    int getPm10IndexId() const;
    std::string getPm10IndexName() const;

    int getPm25IndexId() const;
    std::string getPm25IndexName() const;

    int getO3IndexId() const;
    std::string getO3IndexName() const;
};

#endif // AIR_QUALITY_INDEX_H
