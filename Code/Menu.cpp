#include "Menu.h"
#include "AirTravelManager.h"





void Menu::menu() {
    AirTravelManager aux;
    aux.readAirports();
    aux.readAirlines();
    aux.readFlights();

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

        int choice = 0;
        cout << "What type of location you want to choose for source? (1,2,3,4)" << endl;
        cin >> choice;
        string location, lat, longi;
        vector<string> v;
        switch(choice){
            case 1:
                //names with spaces are not working
                cout << "Airport name or code: ";
                cin >> location;
                if(!aux.findAirport(location)) {
                    cout << "Airport not found!" << endl;
                    break;
                }
                v.push_back(location);
                menu2(v);
                break;

            case 2:
                //names with spaces are not working
                cout << "City name: ";
                cin >> location;
                if(!aux.findCity(location)) {
                    cout << "City not found!" << endl;
                    break;
                }
                v = aux.citytoAirport(location);
                menu2(v);
                break;

            case 3:
                //names with spaces are not working
                cout << "Country name: ";
                cin >> location;
                if(!aux.findCountry(location)) {
                    cout << "Country not found!" << endl;
                    break;
                }
                v = aux.countrytoAirport(location);
                menu2(v);
                break;

            case 4:
                cout << "Latitude: ";
                cin >> lat;
                cout << "Longitude: ";
                cin >> longi;
                v = aux.geotoAirport(lat, longi);
                menu2(v);
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

void Menu::menu2(vector<string> &sourc) {
    AirTravelManager aux;

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

        int choice = 0;
        cout << "What type of location you want to choose for destiny? (1,2,3,4)" << endl;
        cin >> choice;
        string location, lat, longi;
        vector<string> v;
        switch (choice) {
            case 1:
                //names with spaces are not working
                cout << "Airport name or code: ";
                cin >> location;
                if (!aux.findAirport(location)) {
                    cout << "Airport not found!" << endl;
                    break;
                }
                v.push_back(location);
                menu3(sourc, v);
                break;

            case 2:
                //names with spaces are not working
                cout << "City name: ";
                cin >> location;
                if (!aux.findCity(location)) {
                    cout << "City not found!" << endl;
                    break;
                }
                v = aux.citytoAirport(location);
                menu3(sourc, v);
                break;

            case 3:
                //names with spaces are not working
                cout << "Country name: ";
                cin >> location;
                if (!aux.findCountry(location)) {
                    cout << "Country not found!" << endl;
                    break;
                }
                v = aux.countrytoAirport(location);
                menu3(sourc, v);
                break;

            case 4:
                cout << "Latitude: ";
                cin >> lat;
                cout << "Longitude: ";
                cin >> longi;
                v = aux.geotoAirport(lat, longi);
                menu3(sourc, v);
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

void Menu::menu3(vector<string> &sourc, vector<string> &dest) {
    AirTravelManager aux;

    cout << "|-----------------------------------|" << endl;
    cout << "|  Do you want to apply filters?    |" << endl;
    cout << "|-----------------------------------|" << endl;
    cout << "| 1-> Yes                           |" << endl;
    cout << "| 2-> No                            |" << endl;
    cout << "|-----------------------------------|" << endl;

    int choice = 0;
    cin >> choice;

    switch (choice) {
        case 1:
            menu4(sourc, dest);
            break;

        case 2:
            aux.findFlights(sourc, dest);
            break;

        default:
            cout << "Invalid choice!" << endl;
            return;
    }
}

void Menu::menu4(vector<string> &sourc, vector<string> &dest) {
    AirTravelManager aux;

    while (true) {
        cout << "|-----------------------------------|" << endl;
        cout << "|           Filters                 |" << endl;
        cout << "|-----------------------------------|" << endl;
        cout << "| 1-> Choose Airlines               |" << endl;
        cout << "| 2-> Minimize number of Airlines   |" << endl;
        cout << "|                                   |" << endl;
        cout << "|-----------------------------------|" << endl;

        int choice = 0;
        cout << "What type of filters do you want? (1,2)" << endl;
        cin >> choice;
        string input, airline;
        vector<string> airlines;
        istringstream iss;

        switch (choice) {
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