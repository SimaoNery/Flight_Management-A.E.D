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

    /// Reads the csv with the Airport information and puts the information in the right structures \n
    ///O(n)
    void readAirports();
    /// Reads the csv with the Airline information and puts the information in the right structures \n
    ///O(n)
    void readAirlines();
    /// Reads the csv with the Flight information and puts the information in the right structures \n
    ///O(n²)
    void readFlights();

    /// Prints the total number of airports, airlines and flights \n
    /// O(V) -> V = number of airports
    void globalStats() const;
    /// Prints the number of flights departing from an Airport and the number of Airlines that do those flights (can also print a list of all the destinations and airlines) \n
    /// O(V + E) -> V = number of airports, E = number of flights
    /// \param airport Chosen Airport
    void airportInfo(const string& airport) const;
    /// Prints the number of flights an Airline does and the number of airports those airlines flight from (can also print a list of all source-destination flights) \n
    /// O(V * (E + A)) -> V = number of airports, E = number of flights, A = number of airlines
    /// \param airline Chosen Airline
    void airlineFlights(const string& airline) const;
    /// Prints the number of airports in the city, the total of flights leaving the city and the number of airlines responsible for those flights (can print a list of flights from each airport in the city) \n
    /// O(V * E) -> V = number of airports, E = number of flights
    /// \param city Chosen City
    void cityFlights(const string& city);
    /// Prints the number of countries we can travel to from the chosen airport (can print a list of all the countries) \n
    /// O(V * E) -> V = number of airports, E = number of flights
    /// \param airport Chosen Airport
    void airportCountries(const string& airport) const;
    /// Prints the number of countries we can travel to from the chosen city (can print a list of all the countries) \n
    /// O(V * E) -> V = number of airports, E = number of flights
    /// \param city Chosen city
    void citiesCountries(const string& city) const;
    /// Prints the number of countries, cities and airports you can flight to directly from the chosen airport (can print a list with all the countries, cities and airports) \n
    /// O(V * E * log n) -> V = number of airports, E = number of flights
    /// \param airport Chosen airport
    void airportDestinations(const string& airport) const;
    /// Prints a the number of countries, cities and airports we can travel to from the chosen airport in the number of stops given (can print a list with all the airports their cities and their countries) \n
    /// O(V + E) -> V = number of airports, E = number of flights
    /// \param airport Chosen airport
    /// \param stops Number of stops that can be done
    void reachable_destinations(string airport, int stops) const;
    /// Prints the maximum trip in the all Travel System and the Source-Destination pairs that are that distant from each other \n
    /// O(V * (V + E)) -> V = number of airports, E = number of flights
    void maximum_trip() const;
    /// Prints the top airports with the most flight in descending order \n
    /// O(V * log V) -> V = number of airports
    /// \param k Amount of results chosen
    void top_airports(int k) const;
    /// Prints the top airports with the least amount of flights \n
    /// O(V * log V) -> V = number of airports
    /// \param k Amount of results chosen
    void top_airports_low(int k) const;
    /// Prints the number of essential airports in the Flight System (can print a list with all those airports) using a algorithm very similar to Tarjan's Algorithm \n
    /// O(V + E log n) -> V = number of airports, E = number of flights
    void articulation_points() const;
    ///Prints the number of strongly connected components in the graph \n
    /// O(V + E) -> V = number of airports, E = number of flights
    void strongly_connected_components() const;
    /// Checks if an airport exists \n
    /// O(n)
    /// \param code chosen Airport code
    /// \return true if the Airport exists
    bool findAirport(string& code);
    /// Checks if a city exists \n
    /// O(n)
    /// \param city chosen City
    /// \return true if the City exists
    bool findCity(string& city);
    /// Checks if a country exists \n
    /// O(n)
    /// \param country Chosen country
    /// \return true if the Country exists
    bool findCountry(string& country);
    /// Checks if an airline exists \n
    /// O(n)
    /// \param code Chosen Airline code
    /// \return true if the Airline exists
    bool findAirline(string& code);
    /// Adds to a vector all the airports in the chosen city \n
    /// O(n)
    /// \param city Chosen city
    /// \return Vector with all the airports in the city
    vector<string> cityToAirport(string& city);
    /// Adds to a vector all the airports in the chosen country \n
    /// O(n)
    /// \param country Chosen country
    /// \return Vector with all the airports in the country
    vector<string> countryToAirport(string& country);
    /// Calculates the closest distance and add to the vector all the airports at that distance \n
    /// O(n)
    /// \param lat Chosen latitude
    /// \param longi Chosen longitude
    /// \return Vector with the closest airports of the given coordinates
    vector<string> geoToAirport(string& lat, string& longi);
    /// Calculates the distance between to points on the earth \n
    /// O(1)
    /// \param lat1 Latitude of the first object
    /// \param lon1 Longitude of the first object
    /// \param lat2 Latitude of the second object
    /// \param lon2 Longitude of the second object
    /// \return Distance of 2 points
    static double haversine(double lat1, double lon1, double lat2, double lon2);
    /// Finds the best path between all the combinations of source-destination airports(if it is a country or city) and prints them \n
    /// O(n^3)
    /// \param source Source Airport
    /// \param destination Destination Airport
    /// \param air Airlines chosen
    /// \param picky Airports not to stop
    void findFlights(vector<string> &source, vector<string> &destination, vector<string> &air, vector<string> &picky, vector<string> &cit, vector<string> &countries);
    ///Finds the best flight between a source and a destination airport using the minimal airline possible \n
    /// O(V + E) -> V = number of airports, E = number of flights
    /// \param source Source Airport
    /// \param destination Destination Airport
    void findFlightsMin(vector<string> &source, vector<string> &destination);
    /// Finds the best path between a source and a destination airport \n
    /// O(V + E) -> V = number of airports, E = number of flights
    /// \param source Source Airport()
    /// \param destination Destination Airport
    /// \return Vector with the bestPath (all the best path if more than one)
    vector<string> bestPath(string &source, string &destination);
    /// Finds the best path between a source and a destination airport using only the desired airlines \n
    /// O(V + E) -> V = number of airports, E = number of flights
    /// \param source Source Airport
    /// \param destination Destination Airport
    /// \param airlines Desired Airlines
    /// \return Vector with the bestPath filtered
    vector<string> bestPathFiltered(string &source, string &destination, vector<string> &airlines);
    /// Finds the best path between a source and a destination airport without stopping in the said airports \n
    /// O(V + E) -> V = number of airports, E = number of flights
    /// \param source Source Airport
    /// \param destination Source Destination
    /// \param airports Airports to avoid
    /// \return Vector with the best path filtered
    vector<string> bestPathPickyAirports(string &source, string &destination, vector<string> &airports);
    /// Finds the best path between a source and a destination airport without stopping in the said cities \n
    /// O(V + E) -> V = number of airports, E = number of flights
    /// \param source Source Airport
    /// \param destination Destination Airport
    /// \param cities Cities to avoid
    /// \return Vector with the best path filtered
    vector<string> bestPathPickyCities(string &source, string &destination, vector<string> &cit);
    /// Finds the best path between a source and a destination airport without stopping in the said countries \n
    /// O(V + E) -> V = number of airports, E = number of flights
    /// \param source Source Airport
    /// \param destination Destination Airport
    /// \param countries Countries to avoid
    /// \return Vector with the best path filtered
    vector<string> bestPathPickyCountries(string &source, string &destination, vector<string> &countries);
};


#endif //PROJAED2_AIRTRAVELMANAGER_H
