#ifndef EDGE_H
#define EDGE_H

#include <string>

using namespace std;

class State;

class Edge
{
    public:
        Edge();
        ~Edge();
        string arc;
        State* source;
        State* target;
    private:
};

#endif // EDGE_H
