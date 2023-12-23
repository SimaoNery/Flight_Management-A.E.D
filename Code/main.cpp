#include <iostream>
#include "AirTravelManager.h"
#include "Menu.h"

int main() {
    cout << "\n" << "Getting information...." << "\n";

    AirTravelManager manager;
    manager.readAirlines();
    manager.readAirports();
    manager.readFlights();

    Menu menu;
    menu.menu(manager);

    cout << "Information acquired!" << "\n" << "\n";

    return 0 ;
}
