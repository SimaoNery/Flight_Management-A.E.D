#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>
#include <set>
#include "TravelManager.h"

void TravelManager::readAirlines(){

    ifstream inputFile("airlines.csv");
    string line;
    getline(inputFile, line);

    while (getline(inputFile, line)) {
        string code, name, callsign, country;
        istringstream ss(line);
        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, callsign, ',');
        getline(ss, country);

        Airline* airline = new Airline(code, name, callsign, country);
        airlines.insert({code,airline});
    }
}

void TravelManager::readAirports(){
    ifstream inputFile("airports.csv");
    string line;
    getline (inputFile, line);

    while (getline(inputFile, line)) {
        string code, name, city, country, latitude, longitude;
        istringstream ss2(line);
        getline(ss2, code, ',');
        getline(ss2, name, ',');
        getline(ss2, city, ',');
        getline(ss2, country, ',');
        getline(ss2, latitude, ',');
        getline(ss2, longitude);

        if (cities.empty() || cities.find(city + "/" + country) == cities.end()) {
            City* newCity = new City(city, country);
            cities.insert({city + "/" + country, newCity});
        }

        Airport* airport = new Airport(code, name, city, stof(latitude), stof(longitude));
        airports.insert({code, airport});

        cities[city + "/" + country]->addAirport(airport);
    }
}

void TravelManager::readFlights(){
    ifstream inputFile3("flights.csv");
    string line;
    getline(inputFile3, line);

    while (getline(inputFile3, line)) {
        string source, target, airline;

        istringstream ss(line);
        getline(ss, source, ',');
        getline(ss, target, ',');
        getline(ss, airline);

        Flight flight = Flight(target, airline);

        airports[source]->addFlight(flight);
    }
}