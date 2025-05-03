// StationManager.h
#ifndef STATIONMANAGER_H
#define STATIONMANAGER_H

#include <vector>
#include "Station.h"
#include "ApiClient.h"

void loadStations(std::vector<Station>& stations, const std::string& cityFilter = "");

#endif // STATIONMANAGER_H
