#include <cmath>
#include <algorithm>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
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


//----------------------------------Reachable Airports------------------------------------------------------------------------------------------------------------------------------------//
void AirTravelManager::reachable_destinations(string airport, int stops) { //basically a bfs
    unordered_set<string> cities;
    unordered_set<string> countries;

    Airport s = Airport(airport);
    auto source = bigGraph.findVertex(s);
    if(source == nullptr){ return;}

    for(auto vert : bigGraph.getVertexSet()){
        vert->setVisited(false);
    }

    queue<Vertex<Airport> *> aux;
    aux.push(source);

    while(!aux.empty() && stops >= 0){
        int tamanho = aux.size();
        for(int i = 0; i < tamanho; i++){
            auto current = aux.front();
            aux.pop();
            airportCity.insert(make_pair(current->getInfo().getCode(), make_pair(current->getInfo().getCity(), current->getInfo().getCountry())));
            cities.insert(current->getInfo().getCity());
            countries.insert(current->getInfo().getCountry());

            for(auto edge : current->getAdj()){
                auto destination = edge.getDest();
                if(!destination->isVisited()){
                    aux.push(destination);
                    destination->setVisited(true);
                }
            }
        }
        stops--;
    }
    char reachable_choice;
    cout << "Do you want to receive a list of the information (0) or values (1)?";
    cin >> reachable_choice;
    if(reachable_choice == '1'){
        cout << "------------------------------------------------------------" << "\n";
        cout << "From airport " << airport << "-" << source->getInfo().getName() << ", with " << stops << " stops, it's possible to reach: " << "\n" << "\n";
        cout << airportCity.size() << " airports  |   ";
        cout << cities.size() << " cities  |  ";
        cout << countries.size() <<" countries" << "\n";
        cout << "------------------------------------------------------------" << "\n";
    }
    else if(reachable_choice == '0'){
        cout << "------------------------------------------------------------" << "\n";
        cout << "From airport " << airport << "-" << source->getInfo().getName() << ", with " << stops << " stops, it's possible to reach: " << "\n" << "\n";
        for(const auto& pair : airportCity){
            cout << "->" << pair.first << " in " << pair.second.first << ", " << pair.second.second << ";" << "\n";
        }
        cout << "------------------------------------------------------------" << "\n";
    }
    else{
        cout << "Invalid input! Please try again." << "\n";
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//----------------------Maximum Trip(s)--------------------------------------------------------------------------------------------------------------------------------------------------//
void AirTravelManager::maximum_trip() {
    int diameter = 0;
    vector<pair<string, string>> res;

    for(auto vert : bigGraph.getVertexSet()){
        for(auto v : bigGraph.getVertexSet()){
            v->setVisited(false);
        }

        int distance = 0;
        vector<Airport> path;

        queue<Vertex<Airport> *> aux;
        aux.push(vert);
        vert->setVisited(true);
        path.push_back(vert->getInfo());

        while(!aux.empty()){
            int tamanho = aux.size();
            for(int i = 0; i < tamanho; i++){
                auto current = aux.front();
                aux.pop();

                for(auto edge : current->getAdj()){
                    auto destination = edge.getDest();
                    if(!destination->isVisited()){
                        aux.push(destination);
                        destination->setVisited(true);
                        path.push_back(destination->getInfo());
                    }
                }
            }
            distance++;
            if(distance > diameter){
                diameter = distance;
                res.clear();
                res.emplace_back(path.front().getCode(), path.back().getCode());
            }
            else if(distance == diameter){
                res.emplace_back(path.front().getCode(), path.back().getCode());
            }
        }
        path.clear();
    }

    cout << "-----------------------------------------------" << "\n";
    cout << "The maximum trip has: " << diameter << " stops! \n";
    for(auto item : res){
        cout << "Start: " << item.first << " | End: " << item.second << "\n";
    }
    cout << "----------------------------------------------" << "\n";
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//----------Top k Airports-------------------------------------------------------------------------------------------------------------------------------------------------------------//
struct AirportFlights{ // struct to order by int
    Airport airport;
    int flights;

    bool operator<(const AirportFlights& other) const {
        if(flights == other.flights){
            return airport.getCode() < other.airport.getCode();
        }
        return flights > other.flights;
    }
};

void AirTravelManager::top_airports(int k) const{
    set<AirportFlights> res;
    for(auto vert : bigGraph.getVertexSet()){
        int count = vert->getAdj().size();
        AirportFlights airportFlights{vert->getInfo(), count};
        res.insert(airportFlights);
    }

    int aux = 0;
    cout << "--------------------------------------------------------------" << "\n";
    cout << "         This are the top " << k << " airports: " << "\n";
    cout << "--------------------------------------------------------------" << "\n";
    for(auto value : res){
        if(aux > k){
            cout << "--------------------------------------------------------------" << "\n";
            return;
        }
        cout << value.airport.getCode() << "-" << value.airport.getName() << ": " << value.flights << " flights;" << "\n";
        aux++;
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//--------Articulation Points----------------------------------------------------------------------------------------------------------------------------------------------------------//
void AirTravelManager::articulation_points() {

}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//