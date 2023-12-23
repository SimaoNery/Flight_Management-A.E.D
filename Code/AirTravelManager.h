#ifndef PROJAED2_AIRTRAVELMANAGER_H
#define PROJAED2_AIRTRAVELMANAGER_H

#include <map>
#include <set>
#include <list>
#include <unordered_set>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"
using namespace std;

class AirTravelManager {
public:
    unordered_map<string, pair<string, pair<string, string>>> airports; //all airports(code | name | city | country)
    unordered_map<string, string> airlines; //all airlines(will help with statistic type questions)sets are faster
    unordered_set<string> cities; //all cities

    Graph<Airport> bigGraph; //graph with every flight existent(will help in filters)

    void readAirports();
    void readAirlines();
    void readFlights();

    void globalStats() const;
    void airportInfo(const string& airport) const;
    void airlineFlights(const string& airline) const;
    void cityFlights(const string& city);
    void airportCountries(const string& airport) const;
    void citiesCountries(const string& city) const;
    void airportDestinations(const string& airport) const;
    void reachable_destinations(string airport, int stops);
    void maximum_trip();
    void top_airports(int k) const;
    void articulation_points() const;

    bool findAirport(string& code);
    bool findCity(string& city);
    bool findCountry(string& country);
    bool findAirline(string& code);

    vector<string> cityToAirport(string& city);
    vector<string> countryToAirport(string& country);
    vector<string> geoToAirport(string& lat, string& longi);


    void findFlights(vector<string> &source, vector<string> &destination);
    void findFlightsAirlines(vector<string> &source, vector<string> &destination, vector<string> &airlines);
    void findFlightsMin(vector<string> &source, vector<string> &destination);

    vector<string> bestPath(string &source, string &destination);
};


#endif //PROJAED2_AIRTRAVELMANAGER_H
