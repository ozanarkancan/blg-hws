#ifndef GRAPH_H
#define GRAPH_H

#include "Cell.h"
#include <deque>

using namespace std;

class Graph
{
    public:
        ~Graph();
        Graph(unsigned short int, unsigned short int, unsigned short int, deque<Cell>&);//Creates graph as an adjacency matrix by given network
        void DetectAllPath(); //Find all path from injected node to reachable destination by using modified depth first search algorithm
        void PrintAllInjectedComputer(); //Prints all infected computer and infection time
        void CheckComputerIsInjected(unsigned short int); //Controls if a computer is injected
    private:
        unsigned short int numberOfNodes;
        unsigned short int injectionTime;
        unsigned short int firstInjectedComputer;
        Cell** graphMatrix; //adjacency matrix
        deque<Cell> Stack; // Stack for dfs
        deque< deque<Cell> > Explored; //List for trace data
};

#endif // GRAPH_H
