#include "Graph.h"

template <class T>
vector<string> Graph<T>::bfs_bestPaths(const string &source, const string &dest) const {
    vector<T> dests;
    vector <string > res;
    string path = "";
    auto s = findVertex(source);
    auto d = findVertex(dest);
    queue<Vertex<T> *> q;
    for(auto v : vertexSet) {
        v->visited = false;
        v->distance = 0;
    }
    q.push(s);
    s->visited = true;
    while(!q.empty()) {
        auto v = q.front();
        q.pop();

        for(auto & e : v->adj) {
            auto w = e.dest;
            if(!w->visited) {
                q.push(w);
                w->visited = true;
                w->distance = v->distance + 1;
                w->prev = v;
                if(w->info == dest) {
                    dests.push_back(w);
                }
            }
        }
    }
    int min = dests[0]->distance;
    for(int i=1; i<dests.size(); i++) {
        if(dests[i]->distance < min) {
            min = dests[i]->distance;
        }
    }
    for(auto it = dests.begin(); it != dests.end(); ) {
        if((*it)->distance > min) {
            it = dests.erase(it);
        }else{
            ++it;
        }
    }
    for(auto r : dests) {
        auto v = r;
        while(v->info != source) {
            path = v->info + " " + path;
            v = v->prev;
        }
        path = v->info + " " + path;
        res.push_back(path);
        path = "";
    }
    return res;
}

