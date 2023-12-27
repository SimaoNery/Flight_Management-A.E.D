#ifndef PROJAED2_AIRTRAVELMANAGER_H
#define PROJAED2_AIRTRAVELMANAGER_H

#include <map>
#include <set>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"
using namespace std;

class AirTravelManager {
public:
    /// Hash table with Airport code, name, city and country
    unordered_map<string, pair<string, pair<string, string>>> airports;
    /// Hash table with Airport code, latitude and longitude
    unordered_map<string, pair<float, float>> coords;
    /// Hash table with Airline code and name
    unordered_map<string, string> airlines;
    /// Unordered_set with all cities
    unordered_set<string> cities;
    /// Graph with all the airports, airlines and flights
    Graph<Airport> bigGraph;

    /// Reads the csv with the Airport information and puts the information in the right structures
    void readAirports();
    /// Reads the csv with the Airline information and puts the information in the right structures
    void readAirlines();
    /// Reads the csv with the Flight information and puts the information in the right structures
    void readFlights();

    /// Prints the total number of airports, airlines and flights
    void globalStats() const;
    /// Prints the number of flights departing from an Airport and the number of Airlines that do those flights (can also print a list of all the destinations and airlines)
    /// \param airport Chosen Airport
    void airportInfo(const string& airport) const;
    /// Prints the number of flights an Airline does and the number of airports those airlines flight from (can also print a list of all source-destination flights)
    /// \param airline Chosen Airline
    void airlineFlights(const string& airline) const;
    /// Prints the number of airports in the city, the total of flights leaving the city and the number of airlines responsible for those flights (can print a list of flights from each airport in the city)
    /// \param city Chosen City
    void cityFlights(const string& city);
    /// Prints the number of countries we can travel to from the chosen airport (can print a list of all the countries)
    /// \param airport Chosen Airport
    void airportCountries(const string& airport) const;
    /// Prints the number of countries we can travel to from the chosen city (can print a list of all the countries)
    /// \param city Chosen city
    void citiesCountries(const string& city) const;
    /// Prints the number of countries, cities and airports you can flight to directly from the chosen airport (can print a list with all the countries, cities and airports)
    /// \param airport Chosen airport
    void airportDestinations(const string& airport) const;
    /// Prints a the number of countries, cities and airports we can travel to from the chosen airport in the number of stops given (can print a list with all the airports their cities and their countries)
    /// \param airport Chosen airport
    /// \param stops Number of stops that can be done
    void reachable_destinations(string airport, int stops) const;
    /// Prints the maximum trip in the all Travel System and the Source-Destination pairs that are that distant from each other
    void maximum_trip();
    /// Prints the top airports with the most flight in descending order
    /// \param k Amount of results chosen
    void top_airports(int k) const;
    /// Prints the number of essential airports in the Flight System (can print a list with all those airports)
    void articulation_points() const;

    /// \param code chosen Airport code
    /// \return true if the Airport exists
    bool findAirport(string& code);
    /// \param city chosen City
    /// \return true if the City exists
    bool findCity(string& city);
    /// \param country Chosen country
    /// \return true if the Country exists
    bool findCountry(string& country);
    /// \param code Chosen Airline code
    /// \return true if the Airline exists
    bool findAirline(string& code);

    /// Adds to a vector all the airports in the chosen city
    /// \param city Chosen city
    /// \return Vector with all the airports in the city
    vector<string> cityToAirport(string& city);
    /// Adds to a vector all the airports in the chosen country
    /// \param country Chosen country
    /// \return Vector with all the airports in the country
    vector<string> countryToAirport(string& country);
    /// Calculates the closest distance and add to the vector all the airports at that distance
    /// \param lat Chosen latitude
    /// \param longi Chosen longitude
    /// \return Vector with the closest airports of the given coordinates
    vector<string> geoToAirport(string& lat, string& longi);
    /// Calculates the distance between to points on the earth
    /// \param lat1 Latitude of the first object
    /// \param lon1 Longitude of the first object
    /// \param lat2 Latitude of the second object
    /// \param lon2 Longitude of the second object
    /// \return Distance of 2 points
    static double haversine(double lat1, double lon1, double lat2, double lon2);

    /// Finds the best path between all the combinations of source-destination airports(if it is a country or city) and prints them
    /// \param source Source Airport
    /// \param destination Destination Airport
    void findFlights(vector<string> &source, vector<string> &destination);
    ///  NOT DONE YET
    /// \param source
    /// \param destination
    /// \param airlines
    void findFlightsAirlines(vector<string> &source, vector<string> &destination, vector<string> &airlines);
    ///  NOT DONE YET
    /// \param source
    /// \param destination
    void findFlightsMin(vector<string> &source, vector<string> &destination);

    /// Finds the best path between a source and a destination airport
    /// \param source Source Airport
    /// \param destination Destination Airport
    /// \return Vector with the bestPath (all the best path if more than one)
    vector<string> bestPath(string &source, string &destination);
};


#endif //PROJAED2_AIRTRAVELMANAGER_H
