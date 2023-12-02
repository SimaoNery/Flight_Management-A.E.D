#include <iostream>
#include "TravelManager.h"

int main() {
    TravelManager manager;
    manager.readAirlines();
    manager.readAirports();
    manager.readFlights();

    return 0;
}
