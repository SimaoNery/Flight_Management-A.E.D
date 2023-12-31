#ifndef FLIGHT_MANAGEMENT_MENU_H
#define FLIGHT_MANAGEMENT_MENU_H

#include <iostream>
#include <sstream>
#include <vector>
#include "AirTravelManager.h"

using namespace std;

class Menu {
    public:
        /// Constructor for the initial menu
        void menu0(AirTravelManager& aux);
        /// Constructor for best flight source choice menu
        void menu1(AirTravelManager& aux);
        /// Constructor for the best flight destination choice menu
        void menu2(AirTravelManager& aux, vector<string> &sourc);
        /// Constructor for the apply filter option menu
        void menu3(AirTravelManager& aux, vector<string> &sourc, vector<string> &dest);
        /// Constructor for the filters options menu
        void menu4(AirTravelManager& aux, vector<string> &sourc, vector<string> &dest, vector<string> &airlines, vector<string> &picky);
        /// Constructor for statistics options menu
        static void menu_S1(AirTravelManager& aux);
};


#endif //FLIGHT_MANAGEMENT_MENU_H
