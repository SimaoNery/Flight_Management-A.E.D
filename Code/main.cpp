#include <iostream>
#include "AirTravelManager.h"
#include "Menu.h"

int main() {
    cout << "\n" << "Getting information...." << "\n";

    AirTravelManager manager;
    manager.readAirlines();
    manager.readAirports();
    manager.readFlights();

    cout << "Information acquired!" << "\n" << "\n";

    Menu menu;
    menu.menu0(manager);

    return 0 ;
}
