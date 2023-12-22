#include "Menu.h"
#include "AirTravelManager.h"
#include <iostream>

Menu::Menu() {
    AirTravelManager manager;
    manager.readAirlines();
    manager.readAirports();
    manager.readFlights();

    string choice1;
    while(true){
        cout << "|------------------------------------------------------------------------|" << endl;
        cout << "|            Statistics(S)           |         Flight Options(F)         |" << endl;
        cout << "|------------------------------------------------------------------------|" << endl;
        cout << "| 1->                                |                                   |" << endl;
        cout << "| 2->                                |                                   |" << endl;
        cout << "| 3->                                |                                   |" << endl;
        cout << "| 4->                                |                                   |" << endl;
        cout << "| 5->                                |                                   |" << endl;
        cout << "| 6->                                |                                   |" << endl;
        cout << "| 7->                                |                                   |" << endl;
        cout << "| 8->                                |                                   |" << endl;
        cout << "| 9->                                |                                   |" << endl;
        cout << "|                                    |                                   |" << endl;
        cout << "|                                    |                                   |" << endl;
        cout << "|                                    |                                   |" << endl;
        cout << "|                                    |                #Press Q to leave  |" << endl;
        cout << "|------------------------------------------------------------------------|" << endl;
        cout << "What type of operation do you want to do? (S or F)" << endl;

    }
}