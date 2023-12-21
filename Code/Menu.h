#ifndef FLIGHT_MANAGEMENT_MENU_H
#define FLIGHT_MANAGEMENT_MENU_H

#include <iostream>
#include <sstream>
#include <vector>
#include "AirTravelManager.h"

using namespace std;

class Menu {
    public:
        void menu(AirTravelManager& aux);
        void menu2(AirTravelManager& aux, vector<string> &sourc);
        void menu3(AirTravelManager& aux, vector<string> &sourc, vector<string> &dest);
        void menu4(AirTravelManager& aux, vector<string> &sourc, vector<string> &dest);
};


#endif //FLIGHT_MANAGEMENT_MENU_H
