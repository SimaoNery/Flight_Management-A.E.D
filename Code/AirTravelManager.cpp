#include <cmath>
#include <algorithm>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <climits>
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

        airports.insert(make_pair(airport.getCode(), make_pair(airport.getName(), make_pair(airport.getCity(), airport.getCountry())))); //airport information (code | name | city | country)
        coords.insert(make_pair(airport.getCode(), make_pair(airport.getLatitude(), airport.getLongitude())));
        cities.insert(city);

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

        airlines.insert(make_pair(airline.getCode(), airline.getName()));
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

        for(const auto& air : airlines){ //will get the information of the airlines and put it has weight to the edges
            if(a.getCode() == air.first){
                a.setName(air.second);
                break;
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
            if(choice == '0'){
                cout << "-------------------------------------------------------------------------" << "\n";
            }

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

    cout << "\n";
    if(choice == '0'){
        cout << "------------------------------------------------------------------------------" << "\n";
    }

    cout << "This flights are made by " << airlines_count.size() << " different airlines!" << "\n";

    if(choice == '0'){
        cout << "------------------------------------------------------------------------------" << "\n";
    }
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
    int count = 0;
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
                cout << "------------------------------------------------------------------------------------" << "\n";
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
                cout << "------------------------------------------------------------------------------------" << "\n";
            }
        }
    }
    cout << "------------------------------------------------------------------------------------" << "\n";

    if(airportCount == 1){
        cout << city << " has " << airportCount << " airport, having a total of "
             << flightsCount << " flights, made by " << airlines_count.size() << " distinct airlines." << endl;
        cout << "------------------------------------------------------------------------------------" << "\n";
        return;
    }
    cout << city << " has " << airportCount << " airports, having a total of "
         << flightsCount << " flights, made by " << airlines_count.size() << " distinct airlines." << endl;
    cout << "------------------------------------------------------------------------------------" << "\n";
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
    unordered_map<string, string> airports_count;

    unsigned count = 0;
    Airport aux;

    char choice;
    cout << "Do you want a list with all the information(0) or just the values(1)?" << "\n";
    cin >> choice;
    for (auto vert : bigGraph.getVertexSet()) { //finds the desired airport
        if(vert->getInfo().getCode() == airport){
            aux = vert->getInfo();
            for (const auto& edge : vert->getAdj()) { //gets the information needed into unordered_sets and unordered_maps
                Vertex<Airport>* destAirport = edge.getDest();
                airports_count.insert(make_pair(destAirport->getInfo().getCode(), destAirport->getInfo().getName()));
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
            cout << "->" << valor.first << "-" << valor.second << "\n";
        }
        cout << "------------------------------------------------------------------------------------";
    }

    cout << "------------------------------------------------------------------------------------";
    cout << "\nFrom " << aux.getCode() << "-" << aux.getName() << ", you can book a flight to: " << "\n";
    cout << "------------------------------------------------------------------------------------" << "\n";
    cout << airports_count.size() << " different airports" << "\n" << cities_count.size() <<
         " varied cities " << "\n" << countries_count.size() << " distinct countries\n";
    cout << "------------------------------------------------------------------------------------" << "\n";
}

//------------------------------------------------------------------------------------------------------------------------------//

//----------------------------------Reachable Airports------------------------------------------------------------------------------------------------------------------------------------//
void AirTravelManager::reachable_destinations(string airport, int stops) const { //basically a bfs
    int stops_cout = stops;

    unordered_map<string, pair<string, string>> airportCity;
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
    cout << "Do you want to receive a list of the information (0) or values (1)?" << "\n";
    cin >> reachable_choice;
    if(reachable_choice == '1'){
        cout << "-------------------------------------------------------------------------------------" << "\n";
        cout << "From airport " << airport << "-" << source->getInfo().getName() << ", with " << stops_cout << " stops, it's possible to reach: " << "\n" << "\n";
        cout << airportCity.size() << " airports  |   ";
        cout << cities.size() << " cities  |  ";
        cout << countries.size() <<" countries" << "\n";
        cout << "-------------------------------------------------------------------------------------" << "\n";
    }
    else if(reachable_choice == '0'){
        cout << "------------------------------------------------------------" << "\n";
        cout << "From airport " << airport << "-" << source->getInfo().getName() << ", with " << stops_cout << " stops, it's possible to reach: " << "\n";
        cout << airportCity.size() << " airports  |   ";
        cout << cities.size() << " cities  |  ";
        cout << countries.size() <<" countries" << "\n";
        cout << "-----------------------------------------------------------" << "\n" << "\n";

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
void AirTravelManager::maximum_trip() const{
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
    cout << "The maximum trip has: " << diameter << " stops! \n" << "\n";
    for(const auto& item : res){
        cout << "Start: " << item.first << " | End: " << item.second << "\n";
    }
    cout << "----------------------------------------------" << "\n";
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//----------Top k Airports_Big-------------------------------------------------------------------------------------------------------------------------------------------------------------//
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
    cout << "----------------------------------------------------------" << "\n";
    cout << "         This are the top " << k << " airports: " << "\n";
    cout << "----------------------------------------------------------" << "\n";
    for(auto value : res){
        if(aux >= k){
            cout << "--------------------------------------------------------------" << "\n";
            return;
        }
        cout << value.airport.getCode() << "-" << value.airport.getName() << ": " << value.flights << " flights;" << "\n" << "\n";
        aux++;
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//-------Top K Airports_Small-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
struct AirportFlightsLow{ // struct to order by int
    Airport airport;
    int flights;

    bool operator<(const AirportFlightsLow& other) const {
        if(flights == other.flights){
            return airport.getCode() < other.airport.getCode();
        }
        return flights < other.flights;
    }
};

void AirTravelManager::top_airports_low(int k) const{
    set<AirportFlightsLow> res;

    for(auto vert : bigGraph.getVertexSet()){
        int count = vert->getAdj().size();
        AirportFlightsLow airportFlights{vert->getInfo(), count};
        res.insert(airportFlights);
    }

    int aux = 0;
    cout << "----------------------------------------------------------" << "\n";
    cout << "         This are the top " << k << " airports: " << "\n";
    cout << "----------------------------------------------------------" << "\n";
    for(auto value : res){
        if(aux >= k){
            cout << "--------------------------------------------------------------" << "\n";
            return;
        }
        cout << value.airport.getCode() << "-" << value.airport.getName() << ": " << value.flights << " flights;" << "\n" << "\n";
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


    char choice;
    cout << "Do you want to receive a list of the information (0) or just the values (1)?" << "\n";
    cin >> choice;

    cout << "------------------------------------------------------------------" << "\n";
    cout << "There are " << res.size() << " essential airports in the network " << "\n";
    cout << "------------------------------------------------------------------" << "\n";
    if(choice == '0'){
        for(auto valor : res){
            cout << valor.getCode() << "-" << valor.getName() << "\n";
        }
        cout << "------------------------------------------------------------------";
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//--------Strongly Connected Components-----------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void strongly_connected_components_aux(Vertex<Airport>* vertex){
    vertex->setVisited(true);
    for(const auto& edge : vertex->getAdj()){
        auto destination = edge.getDest();
        if(!destination->isVisited()){
            strongly_connected_components_aux(destination);
        }
    }
}

void AirTravelManager::strongly_connected_components() const { //works like a normal dfs
    int count = 0;

    for(auto vert : bigGraph.getVertexSet()){
        vert->setVisited(false);
    }

    for(auto vert : bigGraph.getVertexSet()){
        if(!vert->isVisited()){
            strongly_connected_components_aux(vert);
            count++;
        }
    }

    cout << "-------------------------------------------------------------------------------------" << "\n";
    cout << "There are " << count << " strongly connected components in this flight system!" << "\n";
    cout << "-------------------------------------------------------------------------------------" << "\n";
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//------------Best Flights------------------------------------------------------------------------------------------------------------------------------------------------------------//
bool AirTravelManager::findAirport(string &code) {
    for(const auto& airport : airports){
        if(airport.first == code || airport.second.first == code){
            return true;
        }
    }
    return false;
}

bool AirTravelManager::findCity(string &city) {
    for(const auto& airport : airports){
        if(airport.second.second.first == city){
            return true;
        }
    }
    return false;
}

bool AirTravelManager::findCountry(string &country) {
    for(const auto& airport : airports){
        if(airport.second.second.second == country){
            return true;
        }
    }
    return false;
}

bool AirTravelManager::findAirline(string &code) {
    for(const auto& airline : airlines){
        if(airline.first == code || airline.second == code){
            return true;
        }
    }
    return false;
}

vector<string> AirTravelManager::cityToAirport(string &city) {
    vector<string> air;
    for(const auto& airport : airports){
        if(airport.second.second.first == city){
            air.push_back(airport.first);
        }
    }
    return air;
}

vector<string> AirTravelManager::countryToAirport(string &country) {
    vector<string> air;
    for(const auto& airport : airports) {
        if (airport.second.second.second == country) {
            air.push_back(airport.first);
        }
    }
    return air;
}
vector<string> AirTravelManager::geoToAirport(string &lat, string &longi) {
    vector<string> air;
    bool flag = true;
    double shortest;
    for(const auto& airport : coords){ //Calculates the smallest distance
        if(flag) {
           shortest = haversine(airport.second.first, airport.second.second, stod(lat), stod(longi));
           flag = false;
        }else {
            if(haversine(airport.second.first, airport.second.second, stod(lat), stod(longi)) < shortest) {
                shortest = haversine(airport.second.first, airport.second.second, stod(lat), stod(longi));
            }
        }
    }
    for(const auto& airport : coords){ //Adds to the vector the airports at distance == shortest
        if(haversine(airport.second.first, airport.second.second, stod(lat), stod(longi)) == shortest){
            air.push_back(airport.first);
        }
    }
    return air;
}

double AirTravelManager::haversine(double lat1, double lon1, double lat2, double lon2) { //Calculates the distance of a point to another
    double R = 6372.8; // Earth radius in kilometers

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double c = 2 * asin(sqrt(a));
    return R * c;
}

void AirTravelManager::findFlights(vector<string> &source, vector<string> &destination, vector<string> &air, vector<string> &picky) {
    vector<vector<string>> p;

    for(auto& s : source){
        for(auto& d : destination) {
            if(air.empty() && picky.empty()) {
                auto path = bestPath(s, d);
                if(!path.empty()){
                    p.push_back(path);
                }
            }
            if(!air.empty()){
                auto path = bestPathFiltered(s, d, air);
                if(!path.empty()){
                    p.push_back(path);
                }
            }
            if(!picky.empty()){
                auto path = bestPathPicky(s, d, picky);
                if(!path.empty()){
                    p.push_back(path);
                }
            }
        }
    }
    if(p.empty()){
        cout << "-------------------------------------------------" << "\n";
        cout << "There are no flights between those locations!" << "\n";
        cout << "-------------------------------------------------" << "\n";
        return;
    }

    bool flag = true;
    int min, count = 0;
    for(auto& path : p){
        if(flag){
            for(char c : path[0]){
                if(c == ' '){
                    count++;
                }
            }
            min = count;
            count = 0;
            flag = false;
        }else{
            for(char c : path[0]){
                if(c == ' '){
                    count++;
                }
            }
            if(count < min){
                min = count;
                count = 0;
            }
            count = 0;
        }
    }

    for(auto it = p.begin(); it != p.end(); ) {
        for(char c : (*it)[0]){
            if(c == ' '){
                count++;
            }
        }
        if(count > min){
            it = p.erase(it);
        }else{
            ++it;
        }
        count = 0;
    }

    cout << "----------------------------------------" << "\n";
    cout << "The best path for your trip is: " << "\n";
    cout << "----------------------------------------" << "\n";

    for(const auto& path : p){
        cout << "Start: " << "\n";
        for(const auto& airport : path){
            cout << airport << "\n";
        }
        cout << "End!" << "\n";
    }
    cout << "----------------------------------------" << "\n" << "\n";
}

vector<string> AirTravelManager::bestPath(string &source, string &destination) {
    vector<string> res, dests;
    string path;
    Airport ss, dd;

    for(const auto& i: airports){ //creates an Airport(source and destination)
        if(i.first == source || i.second.first == source){
            string code = i.first;
            ss = Airport(code);
        }
        if(i.first == destination || i.second.first == destination){
            string code = i.first;
            dd = Airport(code);
        }
    }

    auto s = bigGraph.findVertex(ss); //gets the vertex
    auto d = bigGraph.findVertex(dd); //gets the vertex
    if(s == nullptr || d == nullptr) {
        return res;
    }

    queue<Vertex<Airport> *> q; //basically a bfs
    for(auto v : bigGraph.getVertexSet()) {
        v->setVisited(false);
        v->setDistance(0);
    }
    q.push(s);
    s->setVisited(true);

    while(!q.empty()) {
        auto v = q.front();
        q.pop();

        for(auto & e : v->getAdj()) {
            auto w = e.getDest();
            if(!w->isVisited()) {
                q.push(w);
                w->setVisited(true);
                w->setDistance(v->getDistance() + 1);
                w->setPrev(v->getInfo());
                if(w->getInfo().getCode() == destination || w->getInfo().getName() == destination) {
                    dests.push_back(w->getInfo().getCode());
                }
            }
        }
    }
    if(dests.empty()){
        return res;
    }
    int min = bigGraph.findVertex(dests[0])->getDistance();
    for(int i=1; i<dests.size(); i++) { //of all the values in dest gets the one with the smallest path
        if(bigGraph.findVertex(dests[i])->getDistance() < min) {
            min = bigGraph.findVertex(dests[i])->getDistance();
        }
    }
    for(auto it = dests.begin(); it != dests.end(); ) { //eliminates the ones with a bigger path
        if(bigGraph.findVertex(*it)->getDistance() > min) {
            it = dests.erase(it);
        }else{
            ++it;
        }
    }
    for(auto r : dests) {
        auto v = bigGraph.findVertex(r);
        if(bigGraph.findVertex(source)){
            while(v->getInfo().getCode() != source) {
                path = v->getInfo().getCode() + " " + path;
                v = bigGraph.findVertex(v->getPrev());
            }
        }
        else{
            while(v->getInfo().getName() != source) {
                path = v->getInfo().getCode() + " " + path;
                v = bigGraph.findVertex(v->getPrev());
            }
        }
        path = v->getInfo().getCode() + " " + path;
        res.push_back(path);
        path = "";
    }
    return res;
}

vector<string> AirTravelManager::bestPathFiltered(string &source, string &destination, vector<string> &airlines) {
    vector<string> res, dests;
    string path;
    Airport ss, dd;

    for(const auto& i: airports){ //creates an Airport(source and destination)
        if(i.first == source || i.second.first == source){
            string code = i.first;
            ss = Airport(code);
        }
        if(i.first == destination || i.second.first == destination){
            string code = i.first;
            dd = Airport(code);
        }
    }

    auto s = bigGraph.findVertex(ss); //gets the vertex
    auto d = bigGraph.findVertex(dd); //gets the vertex
    if(s == nullptr || d == nullptr) {
        return res;
    }

    queue<Vertex<Airport> *> q; //basically a bfs
    for(auto v : bigGraph.getVertexSet()) {
        v->setVisited(false);
        v->setDistance(0);
    }
    q.push(s);
    s->setVisited(true);

    while(!q.empty()) {
        auto v = q.front();
        q.pop();

        for(auto & e : v->getAdj()) {
            if(find(airlines.begin(), airlines.end(),e.getAirline().getCode()) != airlines.end()) {
                auto w = e.getDest();
                if (!w->isVisited()) {
                    q.push(w);
                    w->setVisited(true);
                    w->setDistance(v->getDistance() + 1);
                    w->setPrev(v->getInfo());
                    if (w->getInfo().getCode() == destination || w->getInfo().getName() == destination) {
                        dests.push_back(w->getInfo().getCode());
                    }
                }
            }
        }
    }
    if(dests.empty()){
        return res;
    }
    int min = bigGraph.findVertex(dests[0])->getDistance();
    for(int i=1; i<dests.size(); i++) { //of all the values in dest gets the one with the smallest path
        if(bigGraph.findVertex(dests[i])->getDistance() < min) {
            min = bigGraph.findVertex(dests[i])->getDistance();
        }
    }
    for(auto it = dests.begin(); it != dests.end(); ) { //eliminates the ones with a bigger path
        if(bigGraph.findVertex(*it)->getDistance() > min) {
            it = dests.erase(it);
        }else{
            ++it;
        }
    }
    for(auto r : dests) {
        auto v = bigGraph.findVertex(r);
        if(bigGraph.findVertex(source)){
            while(v->getInfo().getCode() != source) {
                path = v->getInfo().getCode() + " " + path;
                v = bigGraph.findVertex(v->getPrev());
            }
        }
        else{
            while(v->getInfo().getName() != source) {
                path = v->getInfo().getCode() + " " + path;
                v = bigGraph.findVertex(v->getPrev());
            }
        }
        path = v->getInfo().getCode() + " " + path;
        res.push_back(path);
        path = "";
    }
    return res;

}

vector<string> AirTravelManager::bestPathPicky(string &source, string &destination, vector<string> &picky){
    vector<string> res, dests;
    string path;
    Airport ss, dd;

    for(const auto& i: airports){ //creates an Airport(source and destination)
        if(i.first == source || i.second.first == source){
            string code = i.first;
            ss = Airport(code);
        }
        if(i.first == destination || i.second.first == destination){
            string code = i.first;
            dd = Airport(code);
        }
    }

    auto s = bigGraph.findVertex(ss); //gets the vertex
    auto d = bigGraph.findVertex(dd); //gets the vertex
    if(s == nullptr || d == nullptr) {
        return res;
    }

    queue<Vertex<Airport> *> q; //basically a bfs
    for(auto v : bigGraph.getVertexSet()) {
        v->setVisited(false);
        v->setDistance(0);
    }
    q.push(s);
    s->setVisited(true);

    for (auto &code : picky) {
        Airport aux = Airport(code);
        auto out = bigGraph.findVertex(aux);
        if (out != nullptr) {
            out->setVisited(true);
        }
    }

    while(!q.empty()) {
        auto v = q.front();
        q.pop();

        for(auto & e : v->getAdj()) {
            auto w = e.getDest();
            if(!w->isVisited()) {
                q.push(w);
                w->setVisited(true);
                w->setDistance(v->getDistance() + 1);
                w->setPrev(v->getInfo());
                if(w->getInfo().getCode() == destination || w->getInfo().getName() == destination) {
                    dests.push_back(w->getInfo().getCode());
                }
            }
        }
    }
    if(dests.empty()){
        return res;
    }
    int min = bigGraph.findVertex(dests[0])->getDistance();
    for(int i=1; i<dests.size(); i++) { //of all the values in dest gets the one with the smallest path
        if(bigGraph.findVertex(dests[i])->getDistance() < min) {
            min = bigGraph.findVertex(dests[i])->getDistance();
        }
    }
    for(auto it = dests.begin(); it != dests.end(); ) { //eliminates the ones with a bigger path
        if(bigGraph.findVertex(*it)->getDistance() > min) {
            it = dests.erase(it);
        }else{
            ++it;
        }
    }
    for(auto r : dests) {
        auto v = bigGraph.findVertex(r);
        if(bigGraph.findVertex(source)){
            while(v->getInfo().getCode() != source) {
                path = v->getInfo().getCode() + " " + path;
                v = bigGraph.findVertex(v->getPrev());
            }
        }
        else{
            while(v->getInfo().getName() != source) {
                path = v->getInfo().getCode() + " " + path;
                v = bigGraph.findVertex(v->getPrev());
            }
        }
        path = v->getInfo().getCode() + " " + path;
        res.push_back(path);
        path = "";
    }
    return res;
}

void AirTravelManager::findFlightsMin(vector<string> &source, vector<string> &destination) {
    vector<pair<string, set<string>>> res;
    vector<string> dests;
    string path;
    Airport ss, dd;

    for(const auto& i: airports){ //creates an Airport(source and destination)
        if(i.first == source[0] || i.second.first == source[0]){
            string code = i.first;
            ss = Airport(code);
        }
        if(i.first == destination[0] || i.second.first == destination[0]){
            string code = i.first;
            dd = Airport(code);
        }
    }

    auto s = bigGraph.findVertex(ss); //gets the vertex
    auto d = bigGraph.findVertex(dd); //gets the vertex
    if(s == nullptr || d == nullptr) {
        return;
    }

    queue<Vertex<Airport> *> q; //basically a bfs
    for(auto v : bigGraph.getVertexSet()) {
        v->setVisited(false);
    }
    q.push(s);
    s->setVisited(true);

    unordered_map<Vertex<Airport>*, set<string>> airlinesUsed;
    unordered_map<Vertex<Airport>*, int> minAirlines;

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (auto &e : v->getAdj()) {
            auto w = e.getDest();
            set<string> airlines = airlinesUsed[v];
            airlines.insert(e.getAirline().getCode());

            // If the number of airlines used is less than the current minimum, update the distance and previous airport
            if (minAirlines.find(w) == minAirlines.end() || airlines.size() < minAirlines[w]) {
                q.push(w);
                w->setVisited(true);
                airlinesUsed[w] = airlines;
                minAirlines[w] = airlines.size();
                w->setPrev(v->getInfo());
                if (w->getInfo().getCode() == destination[0] || w->getInfo().getName() == destination[0]) {
                    dests.push_back(w->getInfo().getCode());
                }
            }
        }
    }
    if(dests.empty()){
        return;
    }
    int min = minAirlines[bigGraph.findVertex(dests[0])];
    for(int i=1; i<dests.size(); i++) { //of all the values in dest gets the one with the smallest path
        if(minAirlines[bigGraph.findVertex(dests[i])] < min) {
            min = minAirlines[bigGraph.findVertex(dests[i])];
        }
    }
    for(auto it = dests.begin(); it != dests.end(); ) { //eliminates the ones with a bigger path
        if(minAirlines[bigGraph.findVertex(*it)] > min) {
            it = dests.erase(it);
        }else{
            ++it;
        }
    }
    for (auto r : dests) {
        auto v = bigGraph.findVertex(r);
        set<string> airlines = airlinesUsed[v];
        if (bigGraph.findVertex(source[0])) {
            while (v->getInfo().getCode() != source[0]) {
                path = v->getInfo().getCode() + " " + path;
                v = bigGraph.findVertex(v->getPrev());
            }
        } else {
            while (v->getInfo().getName() != source[0]) {
                path = v->getInfo().getCode() + " " + path;
                v = bigGraph.findVertex(v->getPrev());
            }
        }
        path = v->getInfo().getCode() + " " + path;
        res.push_back({path, airlines});
        path = "";
    }

    cout << "----------------------------------------" << "\n";
    cout << "The best path for your trip is: " << "\n";
    cout << "----------------------------------------" << "\n";

    for (const auto &result : res) {
        cout << "Path: " << result.first << "\n";
        cout << "Airlines: ";
        for (const auto &airline : result.second) {
            cout << airline << " ";
        }
        cout << "\n\n";
    }

    cout << "End!" << "\n" << "\n";
    cout << "----------------------------------------" << "\n";
}