#include <cmath>
#include <algorithm>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include "AirTravelManager.h"

//------Read Data---------------------------------------------------------------------------------------------------------------//
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
        Airline a = Airline(airline);

        for(const auto& air : airlines){ //will get the full information of the airlines and put it has weight to the edges
            if(a.getCode() == air.getCode()){
                a = air;
            }
        }


        bigGraph.addEdge(s, t, a);
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------//

//----------Global Stats-------------------------------------------------------------------------------------------------------------------//
void AirTravelManager::globalStats() const{
    unsigned count = 0;
    for(auto vert : bigGraph.getVertexSet()){ //goes through all airports and sums to count the flights they have
        count += vert->getAdj().size();
    }
    cout << "---------------------------------------------------------------------------" << "\n";
    cout << "There are a total of: " << "\n" << airports.size() << " airports  |  " << airlines.size() << " airlines  |  " << count << " flights" << "\n" << "in the network!" << endl;
    cout << "---------------------------------------------------------------------------" << "\n";
}
//----------------------------------------------------------------------------------------------------------------------------------------//

//--------Airport Info--------------------------------------------------------------------------------------------------------------------//
void AirTravelManager::airportInfo(const string& airport) const {
    unordered_map<string, string> airlines_count;

    unsigned count;
    char choice;

    cout << "Do you want a list of the information(0) or just the values(1)?" << "\n";
    cin >> choice;

    for (auto vert : bigGraph.getVertexSet()) {
        if(vert->getInfo().getCode() == airport){ //find the desired airport
            count = vert->getAdj().size(); //get it's size

            cout << "-------------------------------------------------------------------------" << "\n";
            cout << "There are a total of " << count << " flights departing from this airport!" << "\n";

            for (const auto& edge : vert->getAdj()) { //get the information about each airline and the destinations of each flight
                Airline aux = edge.getAirline();

                airlines_count.insert(make_pair(aux.getCode(), aux.getName()));
                if(choice == '0'){
                    cout << "->Destination: " << edge.getDest()->getInfo().getCode() << "-" << edge.getDest()->getInfo().getName() << ";" << "\n";
                }
            }
            break;
        }
    }

    cout << "\n" << "This flights are made by " << airlines_count.size() << " different airlines!" << "\n";
    if(choice == '0'){
        for(const auto& valor : airlines_count){
            cout << valor.first << "-" << valor.second << ";" << "\n";
        }
    }
    cout << "-------------------------------------------------------------------------" << "\n";
}
//----------------------------------------------------------------------------------------------------------------------------------------//

//--------Airline Flights-----------------------------------------------------------------------------------------------------------------//
void AirTravelManager::airlineFlights(const string& airline) const {
    unsigned count = 0;
    Airline aux;

    unordered_set<string> airport;
    unordered_multimap<string, string> flights; //flights from source to destination

    char choice;
    cout << "Do you want a list with all the information(0) or just the values(1)?" << "\n";
    cin >>  choice;

    for (const auto& vert : bigGraph.getVertexSet()) {
        for (const auto &edge: vert->getAdj()) {
            if (edge.getAirline().getCode() == airline) {
                aux = edge.getAirline();
                count++;
                airport.insert(vert->getInfo().getName());
                flights.insert(make_pair(vert->getInfo().getName(), edge.getDest()->getInfo().getName()));
            }
        }
    }
    if(choice == '0') {
        cout << "---------------------------------------------------------" << "\n";
        cout << "Flights: " << "\n";
        cout << "---------------------------------------------------------" << "\n";
        for (const auto &i: flights) {
            cout << i.first << " ✈\uFE0F --> " << i.second << endl;
        }
    }
    cout << "-----------------------------------------------------------------------------------------------------------------" << "\n";
    cout << aux.getCode() << "-" << aux.getName() << " has a total of " << count << " flights, departing from "
         << airport.size() << " distinct airports." << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------" << "\n";
}
//----------------------------------------------------------------------------------------------------------------------------------------//

//----------City Flights------------------------------------------------------------------------------------------------------------------//
void AirTravelManager::cityFlights(const string& city) {
    int airportCount = 0;
    int flightsCount = 0;

    unordered_set<string> airlines_count;
    unordered_set<string> flights;

    char choice;
    cout << "Do you want to receive a list of the information(0), or only the values(1)?" << "\n";
    cin >> choice;

    for (const auto& vert : bigGraph.getVertexSet()) {
        if(vert->getInfo().getCity() == city) { //checks if it's the desired city
            flights.clear(); //for each city gotta start again
            airportCount++;

            if(choice == '0'){
                cout << "------------------------------------------------------------------------" << "\n";
                cout << vert->getInfo().getName() << " Airport Flights:" << endl << "\n";
            }

            for (const auto &edge: vert->getAdj()) {//will get the destinies and count the flights
                flightsCount++;

                Vertex<Airport> *destAirport = edge.getDest();

                airlines_count.insert(edge.getAirline().getCode());
                flights.insert(destAirport->getInfo().getName());
            }
            if(choice == '0') {
                for (const auto &i: flights) { //lists all the destination of flights in an airport
                    cout << "->Destination: " << i << ";" << "\n";
                }
                cout << "------------------------------------------------------------------------------------";
            }
        }
    }
    if(choice == '1'){
        cout << "------------------------------------------------------------------------------------";
    }
    if(airportCount == 1){
        cout << '\n' << city << " has " << airportCount << " airport, having a total of "
             << flightsCount << " flights, made by " << airlines_count.size() << " distinct airlines." << endl;
        cout << "------------------------------------------------------------------------------------";
        return;
    }
    cout << '\n' << city << " has " << airportCount << " airports, having a total of "
         << flightsCount << " flights, made by " << airlines_count.size() << " distinct airlines." << endl;
    cout << "------------------------------------------------------------------------------------";
}
//----------------------------------------------------------------------------------------------------------------------------------------//

//----------Airport Countries-------------------------------------------------------------------------------------------------------------//
void AirTravelManager::airportCountries(const string& airport) const{
    unordered_set<string> countries;
    Airport aux;

    char choice;
    cout << "Do you want a list with all the information(0) or just the values(1)?" << "\n";
    cin >> choice;
    for(auto vert : bigGraph.getVertexSet()){
        if(vert->getInfo().getCode() == airport) { //if desired airport
            aux = vert->getInfo();
            for (const auto &edge: vert->getAdj()) {
                auto destination = edge.getDest();
                countries.insert(destination->getInfo().getCountry());
            }
            break;
        }
    }


    cout << "---------------------------------------------------------------------------------------------------------------------" << "\n";
    cout << "From " << aux.getCode() << "-" << aux.getName() << " we can travel to " << countries.size() << " different countries!" << "\n";
    cout << "---------------------------------------------------------------------------------------------------------------------" << "\n";

    if(choice == '0'){
        for(const auto& valor : countries){
            cout << "->" << valor << "\n";
        }
        cout << "---------------------------------------------------------------------------------------------------------------------" << "\n";
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------//

//----------Cities Countries-------------------------------------------------------------------------------------------------------------//
void AirTravelManager::citiesCountries(const string& city) const {
    unordered_set<string> countries;

    char choice;
    cout << "Do you want a list with all the information(0) or just the values(1)?" << "\n";
    cin >> choice;
    for (auto vert: bigGraph.getVertexSet()) {
        if (vert->getInfo().getCity() == city) { //if desired city
            for (const auto &edge: vert->getAdj()) {
                auto destination = edge.getDest();
                countries.insert(destination->getInfo().getCountry());
            }
        }
    }

    cout << "---------------------------------------------------------------------------------------------------------------------" << "\n";
    cout << "From " << city << " we can travel to " << countries.size() << " different countries!" << "\n";
    cout << "---------------------------------------------------------------------------------------------------------------------" << "\n";

    if (choice == '0') {
        for (const auto& valor: countries) {
            cout << "->" << valor << "\n";
        }
        cout << "---------------------------------------------------------------------------------------------------------------------" << "\n";
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------//

//------------Airport Destinations--------------------------------------------------------------------------------------------------------//
void AirTravelManager::airportDestinations(const string& airport) const {
    unordered_set<string> cities_count;
    unordered_set<string> countries_count;
    unordered_set<string> airports_count;

    unsigned count = 0;
    Airport aux;

    char choice;
    cout << "Do you want a list with all the information(0) or just the values(1)?" << "\n";
    cin >> choice;
    for (auto vert : bigGraph.getVertexSet()) { //finds the desired airport
        if(vert->getInfo().getCode() == airport){
            aux = vert->getInfo();
            for (const auto& edge : vert->getAdj()) { //gets the information needed into unordered_sets
                Vertex<Airport>* destAirport = edge.getDest();
                airports_count.insert(destAirport->getInfo().getCode());
                countries_count.insert(destAirport->getInfo().getCountry());
                cities_count.insert(destAirport->getInfo().getCity());
            }
            break;
        }
    }

    if(choice == '0'){
        cout << "----------------------------" << "\n";
        cout << "Countries: " <<  "\n";
        cout << "----------------------------" << "\n";
        for(const auto& valor : countries_count){
            cout << "->" << valor << "\n";
        }
        cout << "----------------------------" << "\n";
        cout << "\n";

        cout << "----------------------------" << "\n";
        cout << "Cities: " <<  "\n";
        cout << "----------------------------" << "\n";
        for(const auto& valor : cities_count){
            cout << "->" << valor << "\n";
        }
        cout << "----------------------------" << "\n";
        cout << "\n";

        cout << "----------------------------" << "\n";
        cout << "Airports: " <<  "\n";
        cout << "----------------------------" << "\n";
        for(const auto& valor : airports_count){
            cout << "->" << valor << "\n";
        }
        cout << "------------------------------------------------------------------------------------";
    }

    cout << "------------------------------------------------------------------------------------";
    cout << "\nFrom " << aux.getCode() << "-" << aux.getName() << ", you can book a flight to: " << "\n";
    cout << "------------------------------------------------------------------------------------" << "\n";
    cout << airports_count.size() << " different airports" << "\n" << cities_count.size() <<
         " varied cities " << "\n" << countries_count.size() << " distinct countries\n";
    cout << "------------------------------------------------------------------------------------";
}

//------------------------------------------------------------------------------------------------------------------------------//

//----------------------------------Reachable Airports------------------------------------------------------------------------------------------------------------------------------------//
void AirTravelManager::reachable_destinations(string airport, int stops) { //basically a bfs
    int stops_cout = stops;

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
        for(int i = 0; i < tamanho; i++){ //will keep track of when we go down a level and reduce the stops
            auto current = aux.front();
            aux.pop();

            if (current != source) { //if not the airport of origin
                airportCity.insert(make_pair(current->getInfo().getCode(), make_pair(current->getInfo().getCity(), current->getInfo().getCountry())));
                cities.insert(current->getInfo().getCity());
                countries.insert(current->getInfo().getCountry());
            }

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
        cout << "From airport " << airport << "-" << source->getInfo().getName() << ", with " << stops_cout << " stops, it's possible to reach: " << "\n" << "\n";
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
        for(auto v : bigGraph.getVertexSet()){ //got to reset for every airport so that it can go to the full capacity
            v->setVisited(false);
        }

        int distance = -1; //so that it doesn't count the first one
        vector<Airport> path;

        queue<Vertex<Airport> *> aux;
        aux.push(vert);
        vert->setVisited(true);
        path.push_back(vert->getInfo());

        while(!aux.empty()){
            int tamanho = aux.size();
            for(int i = 0; i < tamanho; i++){ //keep track of the level of the graph we are
                auto current = aux.front();
                aux.pop();

                for(auto edge : current->getAdj()){
                    auto destination = edge.getDest();
                    if(!destination->isVisited()){
                        aux.push(destination);
                        destination->setVisited(true);
                        path.push_back(destination->getInfo()); //will put the last airport we have been in a path so that it connects with the source airport
                    }
                }
            }
            distance++;
            if(distance > diameter){ //if we could go lower in the graph
                diameter = distance;
                res.clear(); //throw away this information, it's useless if we can go lower
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
    for(const auto& item : res){
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
void articulation_points_aux(Vertex<Airport>* vert, Vertex<Airport>* parent, int& children, set<Airport>& res, int& num){
    vert->setVisited(true);
    vert->setNum(num); //unique number of the vertex-"identification"
    vert->setLow(num); //low of the vertex
    num++;

    for(const auto& edge : vert->getAdj()){
        auto destination = edge.getDest();
        if(!destination->isVisited()){
            children++; //we got one more child
            articulation_points_aux(destination,vert , children, res, num); //need to process that child
            vert->setLow(min(vert->getLow(), destination->getLow())); //the low of the initial vert will be the lower we can get

            if(parent != NULL && destination->getLow() >= vert->getNum()){ //if it isn't the root(doesn't have a parent so can't be an articulation point)
                //no back edge from childs of the destination to any parent of the current vertex(articulation point)
                res.insert(vert->getInfo());
            }
        }
        else{ //if already visited update the low value
            vert->setLow(min(vert->getLow(), destination->getNum()));
        }

    }
    if(parent == NULL && children > 1) { //checks if it's the root and has more than one child
        res.insert(vert->getInfo());
    }
}

void AirTravelManager::articulation_points() const {
    set<Airport> res;

    for(auto vert : bigGraph.getVertexSet()){ //initialization
        vert->setVisited(false);
        vert->setNum(0);
        vert->setLow(0);
    }

    for(auto vert : bigGraph.getVertexSet()){
        int num = 0;

        if(!vert->isVisited()){ //start
            int children = 0;
            articulation_points_aux(vert, NULL, children, res, num);
        }
    }

    cout << "------------------------------------------------------------------" << "\n";
    cout << "There are " << res.size() << " essential airports in the network: " << "\n";
    for(auto valor : res){
        cout << valor.getCode() << "-" << valor.getName() << "\n";
    }
    cout << "------------------------------------------------------------------";
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//