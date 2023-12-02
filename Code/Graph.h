#ifndef PROJAED2_FLIGHT_H
#define PROJAED2_FLIGHT_H

#include "Airline.h"
#include "Airport.h"
#include <string>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


template <class T>
class Vertex {
    T info;
    vector<Edge<T> > adj;
    bool visited;

    void addEdge(Vertex<T> *dest, double w);

public:
    Vertex(T in);
    T getInfo() const;
    bool isVisited() const;
    void setVisited(bool v);
    const vector<Edge<T>> &getAdj() const;
    void setAdj(const vector<Edge<T>> &adj);
    friend class Graph<T>;
};

template <class T>
class Edge {
    Vertex<T> * dest;
    double weight;
public:
    Edge(Vertex<T> *d, double w);
    Vertex<T> *getDest() const;
    void setDest(Vertex<T> *dest);
    double getWeight() const;
    void setWeight(double weight);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;
public:
    Vertex<T> *findVertex(const T &in) const;
    int getNumVertex() const;
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    vector<Vertex<T> * > getVertexSet() const;
};

#endif //PROJAED2_FLIGHT_H