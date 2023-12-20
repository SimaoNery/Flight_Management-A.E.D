#ifndef PROJAED2_AIRTRAVELMANAGER_H
#define PROJAED2_AIRTRAVELMANAGER_H

#include <map>
#include <set>
#include <list>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"
using namespace std;

class AirTravelManager {
public:
    set<Airport> airports; //all airports(will help with statistic type questions)sets are faster
    set<Airline> airlines; //all airlines(will help with statistic type questions)sets are faster

    Graph<Airport> bigGraph; //graph with every flight existent(will help in filters)

    map<string, pair<string, string>> airportCity;//airport code, <city, country> will be needed to have a constant time look-up
    map<string, pair<int, int>> airportCoordinates;//airport code, <latitude, longitude> will be needed to have a constant time look-up



    void readAirports();
    void readAirlines();
    void readFlights();

    void reachable_destinations(string airport, int stops);
    void maximum_trip();
};


#endif //PROJAED2_AIRTRAVELMANAGER_H
