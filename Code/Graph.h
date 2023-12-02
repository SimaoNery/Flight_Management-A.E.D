#ifndef PROJAED2_FLIGHT_H
#define PROJAED2_FLIGHT_H

#include "Airline.h"
#include "Airport.h"
#include <string>
using namespace std;

class Edge;
class Vertex;
class Graph;

class Vertex{ //airport
    private:
        Airport airport;
        vector<Edge> adj;
        bool visited;

        void addEdge(Vertex *destination, Airline airline);

    public:
        Vertex(Airport airport);

        Airport getAirport();
        bool isVisited();
        bool setVisited();
        vector<Edge> &getAdj();
        void setAdj(vector<Edge> &adj);
        friend class Graph;
};

class Edge{ //flight
private:
    Airline airline;
    Vertex * destination;
public:
    Edge(Vertex *destination, Airline airline);
    Vertex *getDest();
    void setDest(Vertex *dest);
    Airline getAirline();
    void setAirline(Airline airline);
    friend class Graph;
    friend class Vertex;
};

class Graph { //Graph of flights and airports
    private:
        vector<Vertex *> vertexSet;
    public:
        Vertex findVertex(Airport airport);
        bool addVertex(Airport airport);
        bool addEdge(Vertex source, Vertex destination, Airline airline);
        vector<Vertex *> getVertexSet();
};

#endif //PROJAED2_FLIGHT_H