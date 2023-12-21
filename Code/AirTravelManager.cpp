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

Airline AirTravelManager::getAirline(const string& code) {
    for(auto airline: airlines){
        if(airline.getCode() == code){
            return airline;
        }
    }
    throw runtime_error("Airline with code '" + code + "' not found");
}

void AirTravelManager::globalStats() const{
    cout << "\nThere are a total of " << airports.size() << " airports in the network." << endl;
    cout << "There are a total of " << airlines.size() << " airlines in the network." << endl;
    unsigned count=0;
    for(auto vert : bigGraph.getVertexSet()){
        count += vert->getAdj().size();
    }
    cout << "There are a total of " << count << " flights in the network." << endl;
}

void AirTravelManager::airportInfo(Vertex<Airport> *& airport) {
    set<Airline> airlines_count;
    set<string> countries_count;
    unsigned count =0;
    for (auto vert : bigGraph.getVertexSet()) {
        if(vert->getInfo() == airport->getInfo()){
            count = vert->getAdj().size();
            for (const auto& edge : airport->getAdj()) {
                Vertex<Airport>* destAirport = edge.getDest();
                airlines_count.insert(getAirline(edge.getAirline()));
                countries_count.insert(destAirport->getInfo().getCountry());

                cout << '\n' << "AIRPORT: " << destAirport->getInfo().getCode() << " // " << destAirport->getInfo().getName() << " // "
                    << destAirport->getInfo().getCity() << " // " << destAirport->getInfo().getCountry() << endl;
                cout << "AIRLINE: " << getAirline(edge.getAirline()).getCode() << " // " <<
                    getAirline(edge.getAirline()).getName() << endl;
            }
            break;
        }
    }
    cout << "\nThere are a total of " << count << " flights departing from this airport to "
        << countries_count.size() << " different countries by "
            << airlines_count.size() << " distinct companies.\n";
}

void AirTravelManager::airlineFlights(const Airline& airline) const {
    unsigned count = 0;
    set<Airport> airport;
    set<pair<Airport, Airport>> flights;
    for (const auto& vert : bigGraph.getVertexSet()) {
        for (const auto &edge: vert->getAdj()) {
            if (edge.getAirline() == airline.getCode()) {
                count++;
                airport.insert(vert->getInfo());
                flights.insert({vert->getInfo(), edge.getDest()->getInfo()});
            }
        }
    }
    for(auto i: flights){
        cout << '\n' << i.first.getName() << " ✈\uFE0F --> " << i.second.getName() << endl;
    }
    cout << '\n' << airline.getName() << " has a total of " << count << " flights, departing from "
         << airport.size() << " distinct airports." << endl;
}

void AirTravelManager::cityFlights(const string& city) {
    unsigned airportCount = 0;
    unsigned flightsCount = 0;
    set<Airline> airlines_count;
    set<string> countries_count;
    set<pair<string, Airport>> flights;
    for (const auto& vert : bigGraph.getVertexSet()) {
        if(vert->getInfo().getCity() == city){
            flights.clear();
            airportCount++;
            cout << '\n' << vert->getInfo().getName() << " AIRPORT FLIGHTS:" << endl;
            for (const auto &edge: vert->getAdj()) {
                flightsCount++;
                Vertex<Airport>* destAirport = edge.getDest();
                countries_count.insert(destAirport->getInfo().getCountry());
                airlines_count.insert(getAirline(edge.getAirline()));
                flights.insert({edge.getAirline(), destAirport->getInfo()});
            }
            for(auto i: flights){
                cout << '\n' << i.first << " // " << i.second.getName() << " // "
                    << i.second.getCountry() << endl;
            }
        }
    }
    if(airportCount == 1){
        cout << '\n' << city << " has " << airportCount << " airport, having a total of "
             << flightsCount << " flights departing to " << countries_count.size()
                << " different countries by " << airlines_count.size() << " distinct airlines." << endl;
        return;
    }
    cout << '\n' << city << " has " << airportCount << " airports, having a total of "
         << flightsCount << " flights departing to " << countries_count.size()
            << " different countries by " << airlines_count.size() << " distinct airlines." << endl;
}

void AirTravelManager::airportDestinations(Vertex<Airport> *& airport) {
    set<string> cities_count;
    set<string> countries_count;
    set<Airport> airports_count;
    unsigned count =0;
    for (auto vert : bigGraph.getVertexSet()) {
        if(vert->getInfo() == airport->getInfo()){
            for (const auto& edge : airport->getAdj()) {
                Vertex<Airport>* destAirport = edge.getDest();
                airports_count.insert(destAirport->getInfo());
                countries_count.insert(destAirport->getInfo().getCountry());
                cities_count.insert(destAirport->getInfo().getCity());
            }
            break;
        }
    }
    for(auto i:airports_count){
        cout << '\n' << i.getName() << " // " << i.getCity() << " // " << i.getCountry() << endl;
    }

    cout << "\nFrom " << airport->getInfo().getName() << ", you can book a flight to "
        << airports_count.size() << " different airports, departing to " << cities_count.size() <<
            " varied cities in " << countries_count.size() << " distinct countries.\n";
}