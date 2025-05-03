// main.cpp
#include "StationManager.h"
#include <iostream>
#include <vector>
#include <locale>
#include <clocale>   // dla std::setlocale



int main() {
 

    // Ustaw polską locale UTF-8 dla MSYS2
     // Ustaw locale C (MSYS2)
     if (std::setlocale(LC_ALL, "pl_PL.UTF-8") == nullptr) {
        std::cerr << "Błąd ustawiania locale!" << std::endl;
    }

    std::vector<Station> stations;
    std::string cityFilter = "Warszawa";  // Możesz podać dowolne miasto lub pusty ciąg, by nie filtrować
    loadStations(stations, cityFilter);
    
    for (const auto& station : stations) {
        std::cout << "ID stacji: " << station.getId() << std::endl
                  << "Stacja: " << station.getName() 
                  << ", Miasto: " << station.getCity() 
                  << ", Szerokość geograficzna: " << station.getLatitude()
                  << ", Długość geograficzna: " << station.getLongitude() << std::endl;
    }


    // Zatrzymanie programu przed zamknięciem
    std::cout << "Naciśnij Enter, aby zakończyć program..." << std::endl;
    std::cin.get();  // Czeka na naciśnięcie klawisza Enter przed zamknięciem

    return 0;
}

