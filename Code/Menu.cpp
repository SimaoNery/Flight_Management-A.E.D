#include <algorithm>
#include "Menu.h"
#include "AirTravelManager.h"

int readOption(int optionsCount) {
    string option;
    while (true) {
        cout << '\n' << ">> ";
        getline(cin, option);
        cout << endl;

        bool isValid = true; // check if it's a number
        for (char c: option) {
            if (!isdigit(c)) {
                isValid = false;
                break;
            }
        }

        if (isValid) {
            int num = stoi(option); //string to integer

            if (num >= 0 && num <= optionsCount) { //checks if it's in range
                return num;
            }
        }

        cout << "Invalid input, please try again.\n";
    }
}

void Menu::menu0(AirTravelManager& manager) {

    while (true) {
        cout << "|------------------------------------------------------------------------------------|" << endl;
        cout << "|               Find Flights(F)                 |          Statistics(S)             |" << endl;
        cout << "|-----------------------------------------------|------------------------------------|" << endl;
        cout << "| Options:             | Filters:               | Options:                           |" << endl;
        cout << "|-----------------------------------------------|------------------------------------|" << endl;
        cout << "| Source:              | ->Choose Your Airlines | 1-> Global Information             |" << endl;
        cout << "|   -Airport           |                        | 2-> Airport Flights                |" << endl;
        cout << "|   -City              | ->Minimize Airlines    | 3-> City Flights                   |" << endl;
        cout << "|   -Country           |                        | 4-> Airline Flights                |" << endl;
        cout << "|   -Coordinates       | ->Avoid Airports       | 5-> Countries By Airport           |" << endl;
        cout << "|                      |                        | 6-> Countries By City              |" << endl;
        cout << "| Destination:         | ->Avoid Cities         | 7-> Airport Direct Destinations    |" << endl;
        cout << "|   -Airport           |                        | 8-> Airport Reachable Destinations |" << endl;
        cout << "|   -City              | ->Avoid Countries      | 9-> Maximum Trip                   |" << endl;
        cout << "|   -Country           |                        | 10-> Top Airports In Flights       |" << endl;
        cout << "|   -Coordinates       |                        | 11-> Bottom Airports In Flights    |" << endl;
        cout << "|                      |                        | 12-> Essential Airports            |" << endl;
        cout << "|                      |                        | 13-> Strongly Connected Components |" << endl;
        cout << "|                      |                        |                                    |" << endl;
        cout << "|----------------------|------------------------|------------------------------------|" << endl;
        cout << "|                      |                        |                          Q->Leave  |" << endl;
        cout << "|----------------------|------------------------|------------------------------------|" << endl;
        cout << "\n";

        char origin_choice;

        cout << "----------------------" << "\n";
        cout << "Do you want to: " << "\n";
        cout << "----------------------" << "\n"
             << "-> Find a Flight (F)" << "\n"
             << "-> See Statistics (S)" << "\n"
             << "-> Leave (Q)" << "\n";
        cout << "----------------------" << "\n";

        cout << '\n' << ">> ";
        cin >> origin_choice;
        switch (origin_choice) {
            case 'F':
                menu1(manager);
                break;

            case 'S':
                menu_S1(manager);
                break;

            case 'Q':
                cout << "See you next time!";
                exit(0);

            default:
                cout << " !! Option not recognised! Try again. !!" << "\n";
                cout << "\n";
                break;
        }
    }
}

void Menu::menu1(AirTravelManager& manager) {
        cout << " ----------------------------------------------------" << "\n";
        cout << "|                    Type of Sources                 |" << "\n";
        cout << " ----------------------------------------------------" << "\n";
        cout << "| Airport(1) | City(2) | Country(3) | Coordinates(4) |" << "\n";
        cout << " ----------------------------------------------------" << "\n";
        cout << "What type of location you want to choose for source? (1, 2, 3, 4)" << endl;



        cin.ignore();  // Clear the input buffer so that readOption don't freak out
        int option = readOption(4);
        string location, lat, longi;
        vector<string> v;
        switch (option) {
            case 1:
                cout << "Airport name or code: \n";
                cout << '\n' << ">> ";
                getline(cin, location);
                if (!manager.findAirport(location)) {
                    cout << "Airport not found!" << endl;
                    break;
                }
                v.push_back(location);
                menu2(manager, v);
                break;

            case 2:
                cout << "City name: \n";
                cout << '\n' << ">> ";
                getline(cin, location);
                if (!manager.findCity(location)) {
                    cout << "City not found!" << endl;
                    break;
                }
                v = manager.cityToAirport(location);
                menu2(manager, v);
                break;

            case 3:
                cout << "Country name: \n";
                cout << '\n' << ">> ";
                getline(cin, location);
                if (!manager.findCountry(location)) {
                    cout << "Country not found!" << endl;
                    break;
                }
                v = manager.countryToAirport(location);
                menu2(manager, v);
                break;

            case 4:
                cout << "Latitude: \n";
                cout << '\n' << ">> ";
                cin >> lat;
                cout << "Longitude: \n";
                cout << '\n' << ">> ";
                cin >> longi;
                v = manager.geoToAirport(lat, longi);
                menu2(manager, v);
                break;

            case 0:
                cout << "See you next time!";
                exit(0);

            default:
                return;
        }
}

void Menu::menu2(AirTravelManager& manager, vector<string> &sourc) {

    while (true) {
        cout << " ----------------------------------------------------" << "\n";
        cout << "|               Type of Destinations                 |" << "\n";
        cout << " ----------------------------------------------------" << "\n";
        cout << "| Airport(1) | City(2) | Country(3) | Coordinates(4) |" << "\n";
        cout << " ----------------------------------------------------" << "\n";
        cout << "What type of location you want to choose for destiny? (1,2,3,4)" << endl;

        int option = readOption(4);
        string location, lat, longi;
        vector<string> v;
        switch (option) {
            case 1:
                cout << "Airport name or code: \n";
                cout << '\n' << ">> ";
                getline(cin, location);
                if (!manager.findAirport(location)) {
                    cout << "Airport not found!" << endl;
                    break;
                }
                v.push_back(location);
                menu3(manager, sourc, v);
                break;

            case 2:
                cout << "City name: \n";
                cout << '\n' << ">> ";
                getline(cin, location);
                if (!manager.findCity(location)) {
                    cout << "City not found!" << endl;
                    break;
                }
                v = manager.cityToAirport(location);
                menu3(manager, sourc, v);
                break;

            case 3:
                cout << "Country name: \n";
                cout << '\n' << ">> ";
                getline(cin, location);
                if (!manager.findCountry(location)) {
                    cout << "Country not found!" << endl;
                    break;
                }
                v = manager.countryToAirport(location);
                menu3(manager, sourc, v);
                break;

            case 4:
                cout << "Latitude: \n";
                cout << '\n' << ">> ";
                cin >> lat;
                cout << "Longitude: \n";
                cout << '\n' << ">> ";
                cin >> longi;
                v = manager.geoToAirport(lat, longi);
                menu3(manager, sourc, v);
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

void Menu::menu3(AirTravelManager& manager, vector<string> &sourc, vector<string> &dest) {

    cout << " -----------------------------------" << endl;
    cout << "|  Do you want to apply filters?    |" << endl;
    cout << " -----------------------------------" << endl;
    cout << "|     Yes(1)       |      No(2)     |" << endl;
    cout << " ----------------------------------- " << endl;

    int option = readOption(2);
    vector<string> airlines;
    vector<string> picky;
    vector<string> cit;
    vector<string> countries;

    switch (option) {
        case 1:
            menu4(manager, sourc, dest, airlines, picky, cit, countries);
            break;

        case 2:
            manager.findFlights(sourc, dest, airlines, picky, cit, countries);
            menu0(manager);

        default:
            cout << "Invalid choice!" << endl;
            return;
    }
}

void Menu::menu4(AirTravelManager& manager, vector<string> &sourc, vector<string> &dest, vector<string> &airlines, vector<string> &picky, vector<string> &cit, vector<string> &countries) {

    while (true) {
        cout << " ----------------------------------- " << endl;
        cout << "|              Filters              |" << endl;
        cout << " ----------------------------------- " << endl;
        cout << "| 1-> Choose Airlines               |" << endl;
        cout << "| 2-> Minimize Number of Airlines   |" << endl;
        cout << "| 3-> Avoid Airports                |" << endl;
        cout << "| 4-> Avoid Cities                  |" << endl;
        cout << "| 5-> Avoid Countries               |" << endl;
        cout << " ----------------------------------- " << endl;

        cout << "What type of filters do you want?" << endl;

        int option = readOption(5);
        string input, airline, airport, city, country;
        istringstream iss;

        switch (option) {
            case 1:
                cout << "Choose the airlines you want to use (separated by spaces and using only the airlines code): " << endl;
                cout << '\n' << ">> ";
                getline(cin, input);
                iss.str(input);
                while (iss >> airline) {
                    if (!manager.findAirline(airline)) {
                        cout << "Airline not found!" << endl;
                        break;
                    }
                    airlines.push_back(airline);
                }
                manager.findFlights(sourc, dest, airlines, picky, cit, countries);
                menu0(manager);
                break;

            case 2:
                manager.findFlightsMin(sourc, dest);
                menu0(manager);
                break;
            case 3:
                cout << "Choose the airports you want to avoid (separated by spaces and using only the airports code): " << endl;
                cout << '\n' << ">> ";
                getline(cin, input);
                iss.str(input);

                while (iss >> airport) {
                    if (!manager.findAirport(airport)) {
                        cout << "Airport not found!" << endl;
                        break;
                    }
                   picky.push_back(airport);
                }
                manager.findFlights(sourc, dest,airlines ,picky, cit, countries);
                menu0(manager);
                break;

            case 4:
                cout << "Choose the cities you want to avoid (separated by spaces and using only the city name): " << endl;
                cout << '\n' << ">> ";
                getline(cin, input);
                iss.str(input);

                while (iss >> city) {
                    if (!manager.findCity(city)) {
                        cout << "City not found!" << endl;
                        break;
                    }
                    cit.push_back(city);
                }
                manager.findFlights(sourc, dest,airlines ,picky, cit, countries);
                menu0(manager);
                break;

            case 5:
                cout << "Choose the countries you want to avoid (separated by spaces and using only the country name): " << endl;
                cout << '\n' << ">> ";
                getline(cin, input);
                iss.str(input);

                while (iss >> country) {
                    if (!manager.findCountry(country)) {
                        cout << "City not found!" << endl;
                        break;
                    }
                    countries.push_back(country);
                }
                manager.findFlights(sourc, dest,airlines ,picky, cit, countries);
                menu0(manager);
                break;

            default:
                cout << "Invalid choice!" << endl;
                return;
        }
    }
}

void Menu::menu_S1(AirTravelManager &manager) {
    cout << "------------------------------------------------" << "\n";
    cout << "Choose One Option: " << "\n";
    cout << "------------------------------------------------" << "\n";
    cout << " 1-> Global Information;" << endl;
    cout << " 2-> Airport Flight;" << endl;
    cout << " 3-> City Flights;" << endl;
    cout << " 4-> Airline Flights;" << endl;
    cout << " 5-> Countries By Airport;" << endl;
    cout << " 6-> Countries By City;" << endl;
    cout << " 7-> Airport Direct Destinations;" << endl;
    cout << " 8-> Airport Reachable Destinations;" << endl;
    cout << " 9-> Maximum Trip;" << endl;
    cout << " 10-> Top Airports In Flights;" << endl;
    cout << " 11-> Bottom Airports In Flights;" << endl;
    cout << " 12-> Essential Airports;" << endl;
    cout << " 13-> Strongly Connected Components." << endl;
    cout << "------------------------------------------------" << "\n";

    cin.ignore();  // Clear the input buffer so that readOption don't freak out
    int options = readOption(13);

    string airport;
    string city;
    string airline;
    int stops;
    int top;
    int bottom;
    switch(options) {
        case 1:
            manager.globalStats();
            break;

        case 2:
            cout << "-------------------------" << "\n";
            cout << "Insert an airport code:" << "\n";
            cout << "-------------------------" << "\n";

            cout << '\n' << ">> ";
            cin >> airport;

            if(!manager.findAirport(airport)){
                cout << "Airport not found!" << "\n";
                break;
            }
            manager.airportInfo(airport);
            break;

        case 3:
            cout << "-------------------------" << "\n";
            cout << "Insert a city name:" << "\n";
            cout << "-------------------------" << "\n";

            cout << '\n' << ">> ";
            cin >> city;

            if(!manager.findCity(city)){
                cout << "City not found!" << "\n";
                break;
            }
            manager.cityFlights(city);
            break;

        case 4:
            cout << "-------------------------" << "\n";
            cout << "Insert a airline code:" << "\n";
            cout << "-------------------------" << "\n";

            cout << '\n' << ">> ";
            cin >> airline;

            if(!manager.findAirline(airline)){
                cout << "Airline not found!" << "\n";
                break;
            }
            manager.airlineFlights(airline);
            break;

        case 5:
            cout << "-------------------------" << "\n";
            cout << "Insert an airport code:" << "\n";
            cout << "-------------------------" << "\n";

            cout << '\n' << ">> ";
            cin >> airport;

            if(!manager.findAirport(airport)){
                cout << "Airport not found!" << "\n";
                break;
            }
            manager.airportCountries(airport);
            break;

        case 6:
            cout << "-------------------------" << "\n";
            cout << "Insert a city name:" << "\n";
            cout << "-------------------------" << "\n";

            cout << '\n' << ">> ";
            cin >> city;

            if(!manager.findCity(city)){
                cout << "City not found!" << "\n";
                break;
            }
            manager.citiesCountries(city);
            break;

        case 7:
            cout << "-------------------------" << "\n";
            cout << "Insert an airport code:" << "\n";
            cout << "-------------------------" << "\n";

            cout << '\n' << ">> ";
            cin >> airport;

            if(!manager.findAirport(airport)){
                cout << "Airport not found!" << "\n";
                break;
            }
            manager.airportDestinations(airport);
            break;

        case 8:
            cout << "-------------------------" << "\n";
            cout << "Insert an airport code:" << "\n";
            cout << "-------------------------" << "\n";

            cout << '\n' << ">> ";
            cin >> airport;

            if(!manager.findAirport(airport)){
                cout << "Airport not found!" << "\n";
                break;
            }

            cout << "--------------------------------------" << "\n";
            cout << "Insert the number of stops desired:" << "\n";
            cout << "--------------------------------------" << "\n";

            cin.ignore();
            stops = readOption(99);

            manager.reachable_destinations(airport, stops);
            break;

        case 9:
            manager.maximum_trip();
            break;

        case 10:
            cout << "--------------------------------------" << "\n";
            cout << "Insert the number of results desired:" << "\n";
            cout << "--------------------------------------" << "\n";

            top = readOption(3019);

            manager.top_airports(top);
            break;


        case 11:
            cout << "--------------------------------------" << "\n";
            cout << "Insert the number of results desired:" << "\n";
            cout << "--------------------------------------" << "\n";

            bottom = readOption(3019);

            manager.top_airports_low(bottom);
            break;

        case 12:
            manager.articulation_points();
            break;

        case 13:
            manager.strongly_connected_components();
            break;

        default:
            cout << "Invalid Choice!" << "\n";
            break;
    }
}