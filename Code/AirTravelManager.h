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

    bool findAirport(string& code);
    bool findCity(string& city);
    bool findCountry(string& country);
    bool findAirline(string& code);

    vector<string> citytoAirport(string& city);
    vector<string> countrytoAirport(string& country);
    vector<string> geotoAirport(string& lat, string& longi);

    static double haversine(double lat1, double lon1, double lat2, double lon2);

    void findFlights(vector<string> &source, vector<string> &destination);
    void findFlightsAirlines(vector<string> &source, vector<string> &destination, vector<string> &airlines);
    void findFlightsMin(vector<string> &source, vector<string> &destination);

    vector<string> bestPath(string &source, string &destination);
};


#endif //PROJAED2_AIRTRAVELMANAGER_H
