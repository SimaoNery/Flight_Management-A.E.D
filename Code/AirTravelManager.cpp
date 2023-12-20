#include <cmath>
#include <algorithm>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_set>
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

        float latitude = stod(lati); //convert string to float
        float longitude = stod(longi); //convert string to float

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


        Airport s = Airport(source);
        Airport t = Airport(target);


        bigGraph.addEdge(s, t, airline);
    }
}


//----------------------------------Reachable Airports-----------------------------------------------------------------------//
void AirTravelManager::reachable_destinations(string airport, int stops) { //basically a bfs
    unordered_set<string> cities;
    unordered_set<string> countries;
    unordered_set<string> air;

    Airport s = Airport(airport);
    auto source = bigGraph.findVertex(s);
    if(source == nullptr){ return;}

    for(auto vert : bigGraph.getVertexSet()){
        vert->setVisited(false);
    }

    queue<Vertex<Airport> *> aux;
    aux.push(source);

    while(!aux.empty()){
        auto current = aux.front();
        aux.pop();
        cities.insert(current->getInfo().getCity());
        countries.insert(current->getInfo().getCountry());
        air.insert(current->getInfo().getCode());

        for(auto edge : current->getAdj()){
            auto destination = edge.getDest();
            if(!destination->isVisited()){
                aux.push(destination);
                destination->setVisited(true);
            }
        }
    }

    cout << "------------------------------------------------------------" << "\n";
    cout << "From airport " << airport << "-" << source->getInfo().getName() << ", with " << stops << " stops, it's possible to reach: " << "\n" << "\n";

    cout << air.size() << " airports  |   ";
    cout << cities.size() << " cities  |  ";
    cout << countries.size() <<" countries" << "\n";
    cout << "------------------------------------------------------------" << "\n";
}
//------------------------------------------------------------------------------------------------------------------------//
