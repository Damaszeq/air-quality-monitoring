#include <iostream>
#include <vector>
#include "include\Station.h"

using namespace std;

int main() {
    // Przykład użycia
    vector<int> sensors = {1, 2, 3};
    Station station(1, "Stacja 1", "Warszawa", 52.2298, 21.0118);
    station.displayInfo();

    if (station.hasSensor(2)) {
        cout << "Stacja ma czujnik 2." << endl;
    }
    return 0;
}










