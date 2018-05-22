#ifndef GRAPH_H
#define GRAPH_H

#include "Cell.h"
#include <deque>

using namespace std;

class Graph
{
    public:
        ~Graph();
        Graph(unsigned short int, deque<Cell>&);//Creates graph as an adjacency matrix by given network
        int MaxFlow(); //Find Maximum Flow
		void UpdateCapacity(char*); // Update capacities according to scheme
		int IsMaxFlow();
		void CreateResidualGraph();
		void DeleteResidualGraph();
    private:
        unsigned short int numberOfNodes;
        Cell** graphMatrix; //adjacency matrix
        Cell** residualGraph;
        deque<Cell> Stack; // Stack for dfs
        deque<Cell*> Queue; // Queue for Trace
};

#endif // GRAPH_H
