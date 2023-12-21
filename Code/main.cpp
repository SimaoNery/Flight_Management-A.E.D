#include <iostream>
#include "AirTravelManager.h"
#include "Menu.h"

int main() {
    AirTravelManager aux;
    aux.readAirports();
    aux.readAirlines();
    aux.readFlights();
    Menu menu;
    menu.menu(aux);
    return 0;

    /*
    AirTravelManager manager;
    manager.readAirlines();
    manager.readAirports();
    manager.readFlights();
     */

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
    return 0;*/
}
