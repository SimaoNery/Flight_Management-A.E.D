#ifndef PROJAED2_FLIGHT_H
#define PROJAED2_FLIGHT_H

#include "Airline.h"
#include "Airport.h"
#include <string>
using namespace std;

class Graph { //represents all flights between airports

    struct Edge{ //connects to nodes(will represent flights)
        string destination;
        string airline; //airline that operates in each flight
    };

    struct Node{ //will represent the airports
        string airportCode;
        bool visited; //was this node already visited?
        int distance; //distance of a node to a reference node(will be used in traversal)
        vector<Edge> adj; //outgoing edges to adjacent nodes
    };

private:
    int size;
    string airline; //airline associated with the graph
    vector<Node> nodes; //airports


public:
    Graph(string airline);

    void addEdge(string airportCode, string destination, string airline);
    string getAirline();
    vector<Node> getNodes();

};

#endif //PROJAED2_FLIGHT_H