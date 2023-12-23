#include "Menu.h"
#include "AirTravelManager.h"

int readOption(int optionsCount) {
    string option;
    while(true) {
        getline(cin, option);
        cout << endl;
        if(option.length() == 1 && isdigit(option[0]) && stoi(option) <= optionsCount && stoi(option) >= 0) break;
        cout << "Invalid input, please try again.\n";
    }
    return stoi(option);
}

void Menu::menu(AirTravelManager& aux) {

    while(true){
        cout << "|-----------------------------------|" << endl;
        cout << "|           Find Flights            |" << endl;
        cout << "|-----------------------------------|" << endl;
        cout << "| From:                             |" << endl;
        cout << "| 1-> Airport                       |" << endl;
        cout << "| 2-> City                          |" << endl;
        cout << "| 3-> Country                       |" << endl;
        cout << "| 4-> Geographical coordinates      |" << endl;
        cout << "|                                   |" << endl;
        cout << "| 0-> Leave                         |" << endl;
        cout << "|-----------------------------------|" << endl;

        cout << "What type of location you want to choose for source? (1,2,3,4)" << endl;
        int option = readOption(4);
        string location, lat, longi;
        vector<string> v;
        switch(option){
            case 1:
                cout << "Airport name or code: ";
                getline(cin, location);
                if(!aux.findAirport(location)) {
                    cout << "Airport not found!" << endl;
                    break;
                }
                v.push_back(location);
                menu2(aux, v);
                break;

            case 2:
                cout << "City name: ";
                getline(cin, location);
                if(!aux.findCity(location)) {
                    cout << "City not found!" << endl;
                    break;
                }
                v = aux.citytoAirport(location);
                menu2(aux,v);
                break;

            case 3:
                cout << "Country name: ";
                getline(cin, location);
                if(!aux.findCountry(location)) {
                    cout << "Country not found!" << endl;
                    break;
                }
                v = aux.countrytoAirport(location);
                menu2(aux, v);
                break;

            case 4:
                cout << "Latitude: ";
                cin >> lat;
                cout << "Longitude: ";
                cin >> longi;
                v = aux.geotoAirport(lat, longi);
                menu2(aux, v);
                break;

            case 0:
                cout << "See you next time!";
                exit(0);

            default:
                return;
        }
    }
}

void Menu::menu2(AirTravelManager& aux, vector<string> &sourc) {

    while (true) {
        cout << "|-----------------------------------|" << endl;
        cout << "|           Find Flights            |" << endl;
        cout << "|-----------------------------------|" << endl;
        cout << "| To:                               |" << endl;
        cout << "| 1-> Airport                       |" << endl;
        cout << "| 2-> City                          |" << endl;
        cout << "| 3-> Country                       |" << endl;
        cout << "| 4-> Geographical coordinates      |" << endl;
        cout << "|                                   |" << endl;
        cout << "| 0-> Leave                         |" << endl;
        cout << "|-----------------------------------|" << endl;

        cout << "What type of location you want to choose for destiny? (1,2,3,4)" << endl;
        int option = readOption(4);
        string location, lat, longi;
        vector<string> v;
        switch (option) {
            case 1:
                cout << "Airport name or code: ";
                getline(cin, location);
                if (!aux.findAirport(location)) {
                    cout << "Airport not found!" << endl;
                    break;
                }
                v.push_back(location);
                menu3(aux, sourc, v);
                break;

            case 2:
                cout << "City name: ";
                getline(cin, location);
                if (!aux.findCity(location)) {
                    cout << "City not found!" << endl;
                    break;
                }
                v = aux.citytoAirport(location);
                menu3(aux, sourc, v);
                break;

            case 3:
                cout << "Country name: ";
                getline(cin, location);
                if (!aux.findCountry(location)) {
                    cout << "Country not found!" << endl;
                    break;
                }
                v = aux.countrytoAirport(location);
                menu3(aux, sourc, v);
                break;

            case 4:
                cout << "Latitude: ";
                cin >> lat;
                cout << "Longitude: ";
                cin >> longi;
                v = aux.geotoAirport(lat, longi);
                menu3(aux, sourc, v);
                break;

            case 0:
                cout << "See you next time!";
                exit(0);

            default:
                cout << "Invalid choice!" << endl;
                return;
        }
    }
}

void Menu::menu3(AirTravelManager& aux, vector<string> &sourc, vector<string> &dest) {

    cout << "|-----------------------------------|" << endl;
    cout << "|  Do you want to apply filters?    |" << endl;
    cout << "|-----------------------------------|" << endl;
    cout << "| 1-> Yes                           |" << endl;
    cout << "| 2-> No                            |" << endl;
    cout << "|-----------------------------------|" << endl;

    int option = readOption(2);

    switch (option) {
        case 1:
            menu4(aux, sourc, dest);
            break;

        case 2:
            aux.findFlights(sourc, dest);
            break;

        default:
            cout << "Invalid choice!" << endl;
            return;
    }
}

void Menu::menu4(AirTravelManager& aux, vector<string> &sourc, vector<string> &dest) {

    while (true) {
        cout << "|-----------------------------------|" << endl;
        cout << "|           Filters                 |" << endl;
        cout << "|-----------------------------------|" << endl;
        cout << "| 1-> Choose Airlines               |" << endl;
        cout << "| 2-> Minimize number of Airlines   |" << endl;
        cout << "|                                   |" << endl;
        cout << "|-----------------------------------|" << endl;

        cout << "What type of filters do you want? (1,2)" << endl;

        int option = readOption(2);
        string input, airline;
        vector<string> airlines;
        istringstream iss;

        switch (option) {
            case 1:
                cout << "Choose the airlines you want to use (separated by spaces and using only the airlines code): " << endl;
                getline(cin, input);
                iss.str(input);
                while (iss >> airline) {
                    if (!aux.findAirline(airline)) {
                        cout << "Airline not found!" << endl;
                        break;
                    }
                    airlines.push_back(airline);
                }
                //aux.findFlightsAirlines(sourc, dest, airlines);
                break;

            case 2:
                //aux.findFlightsMin(sourc, dest);
                break;

            default:
                cout << "Invalid choice!" << endl;
                return;
        }
    }
}