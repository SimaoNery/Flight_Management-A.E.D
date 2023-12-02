#include "Graph.h"

Graph::Graph(string airline){
    this->airline = airline;
    this->size = 0;
}

void Graph::addEdge(std::string airportCode, std::string destination, std::string airline) {
    Edge edge;
    edge.destination = destination;

    for(int i = 0; i < nodes.size(); i++){ //find the airport of source and add an edge from there to the destination airport
        if(nodes[i].airportCode == airportCode){
            nodes[i].adj.push_back(edge);
            return;
        }
    }
    //if the source city is not already in the graph we add it
    Node novo;
    novo.airportCode = airportCode;
    vector<Edge> destinations;
    destinations.push_back(edge);
    novo.adj = destinations;
    nodes.push_back(novo);
    size++;
}

string Graph::getAirline() {
    return airline;
}

vector<Graph::Node> Graph::getNodes() {
    return nodes;
}