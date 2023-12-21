#include <cmath>
#include <algorithm>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include "AirTravelManager.h"

void AirTravelManager::readAirports(){
    ifstream file("../Information/airports.csv");
    if(!file.is_open()){ //Check if we can open the file
        cout << "Impossible to open the file!" << endl;
    }

    string line; getline(file, line); //Ignore the first line

    while(getline(file, line)) {

        istringstream iss(line);

        string code, name, city, country, lati, longi;
        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, city, ',');
        getline(iss, country, ',');
        getline(iss, lati, ',');
        getline(iss, longi, '\r');

        double latitude = stod(lati); //convert string to double
        double longitude = stod(longi); //convert string to double

        Airport airport(code, name, city, country, latitude, longitude);

        airports.insert(airport); //adds an airport to the set with all airports
        airportCity.insert(make_pair(code, make_pair(city, country))); //adds a pair (code, (city, country)) to the map
        airportCoordinates.insert(make_pair(code, make_pair(latitude, longitude))); //adds a pair(code, (latitude, longitude)) to the other map

        bigGraph.addVertex(airport); //adds the airport as a vertex of the graph
    }
}

void AirTravelManager::readAirlines(){
    ifstream file("../Information/airlines.csv");
    if(!file.is_open()){ //Check if we can open the file
        cout << "Impossible to open the file!" << endl;
    }

    string line; getline(file, line); //Ignore the first line

    while(getline(file, line)) {

        istringstream iss(line);

        string code, name, callSign, country;
        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, callSign, ',');
        getline(iss, country, '\r');

        Airline airline(code, name, callSign, country);

        airlines.insert(airline);
    }
}

void AirTravelManager::readFlights(){
    ifstream file("../Information/flights.csv");
    if(!file.is_open()){ //Check if we can open the file
        cout << "Impossible to open the file!" << endl;
    }

    string line; getline(file, line); //Ignore the first line

    while(getline(file, line)) {

        istringstream iss(line);

        string source, target, airline;
        getline(iss, source, ',');
        getline(iss, target, ',');
        getline(iss, airline, '\r');


        Airport s;
        Airport t;

        for(auto vert : bigGraph.getVertexSet()){
            if(vert->getInfo().getCode() == source){
                s = vert->getInfo();
                break;
            }
        }

        for(auto vert : bigGraph.getVertexSet()){
            if(vert->getInfo().getCode() == target){
                t = vert->getInfo();
                break;
            }
        }
        bigGraph.addEdge(s, t, airline);
    }
}

bool AirTravelManager::findAirport(string &code) {
    for(auto airport : airports){
        if(airport.getCode() == code || airport.getName() == code){
            return true;
        }
    }
    return false;
}

bool AirTravelManager::findCity(string &city) {
    for(auto airport : airports){
        if(airport.getCity() == city){
            return true;
        }
    }
    return false;
}

bool AirTravelManager::findCountry(string &country) {
    for(auto airport : airports){
        if(airport.getCountry() == country){
            return true;
        }
    }
    return false;
}

bool AirTravelManager::findAirline(string &code) {
    for(const auto& airline : airlines){
        if(airline.getCode() == code || airline.getName() == code){
            return true;
        }
    }
    return false;
}

vector<string> AirTravelManager::citytoAirport(string &city) {
    vector<string> air;
    for(const auto& airport : airportCity){
        if(airport.second.first == city){
            air.push_back(airport.first);
        }
    }
    return air;
}

vector<string> AirTravelManager::countrytoAirport(string &country) {
    vector<string> air;
    for(const auto& airport : airportCity){
        if(airport.second.second == country){
            air.push_back(airport.first);
        }
    }
    return air;
}

vector<string> AirTravelManager::geotoAirport(string &lat, string &longi) {
    vector<string> air;
    double latitude = stod(lat);
    double longitude = stod(longi);
    for (const auto &airport: airportCoordinates) {
        if (airport.second.first == latitude && airport.second.second == longitude) {
            air.push_back(airport.first);
        }
    }
    return air;
}

void AirTravelManager::findFlights(vector<string> &source, vector<string> &destination) {
    vector<vector<string>> p;

    for(const auto& s : source){
        for(const auto& d : destination) {
            auto path = bigGraph.bfs_bestPaths(s, d);
            if(!path.empty()){
                p.push_back(path);
            }
        }
    }

    for(const auto& path : p){
        for(const auto& airport : path){
            cout << airport << " ";
        }
        cout << endl;
    }


}
