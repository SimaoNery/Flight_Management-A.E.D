#ifndef FLIGHT_MANAGEMENT_MENU_H
#define FLIGHT_MANAGEMENT_MENU_H

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class Menu {
    public:
        void menu();
        void menu2(vector<string> &sourc);
        void menu3(vector<string> &sourc, vector<string> &dest);
        void menu4(vector<string> &sourc, vector<string> &dest);
};


#endif //FLIGHT_MANAGEMENT_MENU_H
