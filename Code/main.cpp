#include <iostream>
#include "AirTravelManager.h"
#include "Graph.h"

int main() {
    cout << "\n" << "Getting information...." << "\n";

    AirTravelManager manager;
    manager.readAirlines();
    manager.readAirports();
    manager.readFlights();

    cout << "Information acquired!" << "\n" << "\n";

    //manager.globalStats();
    //manager.airportInfo("CDG");
    //manager.airlineFlights("RYR");
    //manager.cityFlights("Paris");
    //manager.airportCountries("CDG");
    //manager.citiesCountries("Paris");
    //manager.airportDestinations("CDG");


    /* Test airports set
    cout << manager.airports.size() << "\n";
    for( auto airport : manager.airports){
        cout << airport.getCode()  << " | " << airport.getName() << " | " << airport.getCountry() << "\n";
    }*/

    /* Test airlines set
    cout << manager.airlines.size() << "\n";
    for( auto airline : manager.airlines){
        cout << airline.getCode()  << " | " << airline.getName() << " | " << airline.getCountry() << "\n";
    }*/

    /* Test Graph Vertexes
    cout << manager.bigGraph.getVertexSet().size() << "\n" << "\n" << "\n";*/
    //Test Graph Edges
    /*int count = 0;
    for(auto vert : manager.bigGraph.getVertexSet()){
        count += vert->getAdj().size();
    }
    cout << count;*/

    /* Test airportCity map
   cout << manager.airportCity.size() << "\n";
   for( auto airport : manager.airportCity){
       cout << airport.first << " | " << airport.second.first << "-" << airport.second.second << "\n";
   }*/


    /* Test airportCoords map
    cout << manager.airportCoordinates.size() << "\n";
    for( auto airport : manager.airportCoordinates){
        cout << airport.first << " | " << airport.second.first << "-" << airport.second.second << "\n";
    }

    //test reachable_destinations
    /*manager.reachable_destinations("JFK", 3);*/

    //test maximum_trip
    /*manager.maximum_trip();*/

    //test top_airports
    /*manager.top_airports(3);*/

    //test articulation_points
    /*manager.articulation_points()*/
    return 0 ;
}
