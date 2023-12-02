#include <iostream>
#include "AirTravelManager.h"

int main() {
    AirTravelManager manager;
    manager.readAirlines();
    manager.readAirports();
    manager.readFlights();

    return 0;
}
