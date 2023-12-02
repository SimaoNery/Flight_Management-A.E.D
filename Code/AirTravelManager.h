#ifndef PROJAED2_AIRTRAVELMANAGER_H
#define PROJAED2_AIRTRAVELMANAGER_H

#include <unordered_map>
#include <unordered_set>
#include <list>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"
using namespace std;

class AirTravelManager {
public:
    void readAirlines();
    void readAirports();
    void readFlights();

private:
    unordered_map<string, Airport*> airports;
    unordered_map<string, City*> cities;
    unordered_map<string, Airline*> airlines;

};


#endif //PROJAED2_AIRTRAVELMANAGER_H
