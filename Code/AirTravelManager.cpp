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
    for(auto airport : airports){
        if(airport.getCity() == city){
            air.push_back(airport.getCode());
        }
    }
    return air;
}

vector<string> AirTravelManager::countrytoAirport(string &country) {
    vector<string> air;
    for(auto airport : airports){
        if(airport.getCountry() == country){
            air.push_back(airport.getCode());
        }
    }
}

vector<string> AirTravelManager::geotoAirport(string &lat, string &longi) {
    vector<string> air;
    bool flag = true;
    double shortest;
    for(auto airport : airports){
        if(flag) {
           shortest = haversine(airport.getLatitude(), airport.getLongitude(), stod(lat), stod(longi));
           flag = false;
        }else {
            if(haversine(airport.getLatitude(), airport.getLongitude(), stod(lat), stod(longi)) < shortest) {
                shortest = haversine(airport.getLatitude(), airport.getLongitude(), stod(lat), stod(longi));
            }
        }
    }
    for(auto airport : airports){
        if(haversine(airport.getLatitude(), airport.getLongitude(), stod(lat), stod(longi)) == shortest){
            air.push_back(airport.getCode());
        }
    }
    return air;
}

double AirTravelManager::haversine(double lat1, double lon1, double lat2, double lon2) {
    double R = 6372.8; // Earth radius in kilometers

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);

    double c = 2 * asin(sqrt(a));

    return R * c;
}

void AirTravelManager::findFlights(vector<string> &source, vector<string> &destination) {
    vector<vector<string>> p;

    for(auto& s : source){
        for(auto& d : destination) {
            auto path = bestPath(s, d);
            if(!path.empty()){
                p.push_back(path);
            }
        }
    }

    for(const auto& path : p){
        for(const auto& airport : path){
            cout << airport;
        }
        cout << endl;
    }
}

vector<string> AirTravelManager::bestPath(string &source, string &destination) {
    vector<string> res, dests;
    string path;
    Airport ss;
    Airport dd;
    for(auto i: airports){
        if(i.getCode() == source || i.getName() == source){
            ss=i;
        }
        if(i.getCode() == destination || i.getName() == destination){
            dd=i;
        }
    }
    auto s = bigGraph.findVertex(ss);
    auto d = bigGraph.findVertex(dd);
    if(s == nullptr || d == nullptr) {
        return res;
    }

    queue<Vertex<Airport> *> q;
    for(auto v : bigGraph.getVertexSet()) {
        v->setVisited(false);
        v->setDistance(0);
    }
    q.push(s);
    s->setVisited(true);
    while(!q.empty()) {
        auto v = q.front();
        q.pop();

        for(auto & e : v->getAdj()) {
            auto w = e.getDest();
            if(!w->isVisited()) {
                q.push(w);
                w->setVisited(true);
                w->setDistance(v->getDistance() + 1);
                w->setPrev(v->getInfo());
                if(w->getInfo().getCode() == destination || w->getInfo().getName() == destination) {
                    dests.push_back(w->getInfo().getCode());
                }
            }
        }
    }
    int min = bigGraph.findVertex(dests[0])->getDistance();
    for(int i=1; i<dests.size(); i++) {
        if(bigGraph.findVertex(dests[i])->getDistance() < min) {
            min = bigGraph.findVertex(dests[i])->getDistance();
        }
    }
    for(auto it = dests.begin(); it != dests.end(); ) {
        if(bigGraph.findVertex(*it)->getDistance() > min) {
            it = dests.erase(it);
        }else{
            ++it;
        }
    }
    for(auto r : dests) {
        auto v = bigGraph.findVertex(r);
        if(bigGraph.findVertex(source)){
            while(v->getInfo().getCode() != source) {
                path = v->getInfo().getCode() + " " + path;
                v = bigGraph.findVertex(v->getPrev());
            }
        }
        else{
            while(v->getInfo().getName() != source) {
                path = v->getInfo().getCode() + " " + path;
                v = bigGraph.findVertex(v->getPrev());
            }
        }
        path = v->getInfo().getCode() + " " + path;
        res.push_back(path);
        path = "";
    }
    return res;
}
