#include <iostream>
#include "Graph.h"
#include <algorithm>

using namespace std;

Graph::Graph(unsigned short int computer, unsigned short int time, unsigned short int numberOfNodes, deque<Cell>& communicationNetwork)
{
    this->numberOfNodes = numberOfNodes; // set number of nodes
    injectionTime = time; // set first injection time
    firstInjectedComputer = computer; // set first infected computer
    Cell current, switched, firstNode;

    //Get memory place for graphMatrix pointer nxn.
    graphMatrix = new Cell*[numberOfNodes];
    for(int i = 0; i < numberOfNodes; i++)
        graphMatrix[i] = new Cell[numberOfNodes];

    //Create list of trace data
    for(int i = 0; i < numberOfNodes; i++)
	{
		deque<Cell> d;
		Explored.push_back(d);
	}

    //Create and add first injected computer to adjacency matrix
    firstNode.destination = firstInjectedComputer;
    firstNode.source = firstInjectedComputer;
    firstNode.timestamp = injectionTime;
    graphMatrix[firstInjectedComputer - 1][firstInjectedComputer - 1] = firstNode;

    //Iterate over network data
    for(unsigned int i = 0; i < communicationNetwork.size(); i++)
    {
        current = communicationNetwork[i];

        //Add an edge both node
        graphMatrix[current.source - 1][current.destination - 1] = current;
        switched = current.switchSourceAndDestination();
        graphMatrix[switched.source - 1][switched.destination - 1] = switched;
    }
}

void Graph::DetectAllPath()
{
    Cell firstNode, current, previous;

    firstNode.destination = firstInjectedComputer;
    firstNode.source = firstInjectedComputer;
    firstNode.timestamp = injectionTime;

    Stack.push_back(firstNode);

    while(Stack.size() != 0)
    {
        current = Stack.back();
        Stack.pop_back();

        if(Explored[current.destination - 1].size() == 0)
        {
            if(previous.timestamp != 0)//For first node
				Explored[current.destination - 1] = Explored[current.source - 1];
            Explored[current.destination - 1].push_back(current);

            for(int i = 0; i < numberOfNodes; i++)
            {
                if(current.destination - 1 != i && current.source - 1 != i && graphMatrix[current.destination - 1][i].timestamp != 0)//Add neighbours
                {
                    Cell neighbour = graphMatrix[current.destination - 1][i];
                    Cell search = neighbour.switchSourceAndDestination();

                    if(neighbour.timestamp >= current.timestamp)
                        Stack.push_back(neighbour);
                }
            }
        }
        else
        {
            Cell forComparison = Explored[current.destination - 1][Explored[current.destination - 1].size() - 1];

            if(current.timestamp < forComparison.timestamp)
            {
                Explored[current.destination - 1] = Explored[current.source - 1];
                Explored[current.destination - 1].push_back(current);
            }
        }
        previous = current;
    }
}

void Graph::PrintAllInjectedComputer()
{
    cout << "\nComputers can be infected by the trace (computer_no timestamp) :" << endl;
    for(unsigned short int i = 0; i < numberOfNodes; i++)
    {
        if(Explored[i].size() != 0)
        {
            Cell c = Explored[i][Explored[i].size() - 1];
            cout << c.destination << "\t" << c.timestamp << endl;
        }
    }
}

void Graph::CheckComputerIsInjected(unsigned short int computer)
{
    if(Explored[computer - 1].size() == 0)//If list of trace data is empty, computer is not infected
        cout << "No" << endl;
    else
    {
        cout << "Yes" << endl;
        cout << "The trace (computer_no timestamp):" << endl;;
        for(unsigned short int i = 0; i < Explored[computer - 1].size(); i++)//Print trace data
        {
            Cell current = Explored[computer - 1][i];
            cout << current.destination << "\t" << current.timestamp << endl;
        }
    }
}

Graph::~Graph()
{
    for(int i = 0; i < numberOfNodes; i++)
    {
        delete[] graphMatrix[i];
    }
    delete[] graphMatrix;
}
