#include <iostream>
#include "Graph.h"
#include <algorithm>
#include <limits.h>
#include <fstream>

using namespace std;

Graph::Graph(unsigned short int numberOfNodes, deque<Cell>& communicationNetwork)
{
    this->numberOfNodes = numberOfNodes; // set number of nodes
    Cell current;

    //Get memory place for graphMatrix and residualGraph pointer nxn.
    graphMatrix = new Cell*[numberOfNodes];

    for(int i = 0; i < numberOfNodes; i++)
        graphMatrix[i] = new Cell[numberOfNodes];
    //Iterate over network data
    for(unsigned int i = 0; i < communicationNetwork.size(); i++)
    {
        current = communicationNetwork[i];

        graphMatrix[current.source - 1][current.destination - 1] = current;
	}
}

int Graph::MaxFlow()
{
    Cell current, sourceNode;
    int flow = 0;
    int min = INT_MAX;

    sourceNode.source = 1;
    sourceNode.destination = 1;
    sourceNode.capacity = 0;
    Stack.push_back(sourceNode);

    while(Stack.size() != 0)
    {
        current = Stack.back();
		current = current.switchSourceAndDestination();
        Stack.pop_back();

		if(Queue.size() != 0)
		{
			while(current.destination < Queue[Queue.size() - 1]->destination)
			{
				Queue.pop_back();
				if(Queue.size() == 0)
					break;
			}
		}

        if(current.source != current.destination)
        {
            Queue.push_back(&residualGraph[current.destination - 1][current.source - 1]);

            if(current.source == numberOfNodes)
            {
                Cell* cPtr;
                for(int i = 0; i < Queue.size(); i++)
                {
					int curCapacity;
                    cPtr = Queue[i];
					curCapacity = graphMatrix[cPtr->source - 1][cPtr->destination - 1].capacity - cPtr->capacity;

                    if(curCapacity < min)
                        min = curCapacity;
                }

                flow += min;
                for(int i = 0; i < Queue.size(); i++)//Show trace
                {
                    cPtr = Queue[i];
                    cout << cPtr->source << "->";
                    cPtr->capacity += min;//Update capacity
                }
                cout << cPtr->destination << " : " << min << endl;
                min = INT_MAX;
                Queue.pop_back();

                continue;
            }
        }

        for(int i = numberOfNodes - 1; i >= current.source; i--)//Branch neighbour
        {
            if(graphMatrix[current.source - 1][i].capacity - residualGraph[current.source - 1][i].capacity > 0)
            {
                Stack.push_back(graphMatrix[current.source - 1][i]);
            }
        }
    }

	Queue.clear();
	DeleteResidualGraph();

    return flow;
}

int Graph::IsMaxFlow()
{
    Cell current, sourceNode;
    int flow = 0;
    int min = INT_MAX;
    bool capacityExceed = false;

    sourceNode.source = 1;
    sourceNode.destination = 1;
    sourceNode.capacity = 0;
    Stack.push_back(sourceNode);

    while(Stack.size() != 0)
    {
        current = Stack.back();
		current = current.switchSourceAndDestination();
        Stack.pop_back();

		if(Queue.size() != 0)
		{
			while(current.destination < Queue[Queue.size() - 1]->destination)
			{
				Queue.pop_back();
				if(Queue.size() == 0)
					break;
			}
		}

        if(current.source != current.destination)
        {
            Queue.push_back(&residualGraph[current.destination - 1][current.source - 1]);

            if(current.source == numberOfNodes)
            {
                Cell* cPtr;
                for(int i = 0; i < Queue.size(); i++)
                {
					int curCapacity;
                    cPtr = Queue[i];
					/*if(cPtr->capacity < 0)
						curCapacity = graphMatrix[cPtr->source - 1][cPtr->destination - 1].capacity + cPtr->capacity;
					else*/
						curCapacity = graphMatrix[cPtr->source - 1][cPtr->destination - 1].capacity - cPtr->capacity;
                    if(curCapacity <= 0)
                    {
                        capacityExceed = true;
						min = INT_MAX;
						while(Queue.size() - 1 >= i)
						{
							Cell* willDelete = Queue.back();
							Queue.pop_back();
							for(int i = 0; i < Stack.size(); i++)
							{
								if(willDelete->source == Stack[i].source)
								{
									Stack.erase(Stack.begin() + i);
									i--;
								}
							}
						}
                        break;
                    }

                    if(curCapacity < min)
                        min = curCapacity;
                }

                if(!capacityExceed)
                {
                    flow += min;
                    for(int i = 0; i < Queue.size(); i++)//Show trace
                    {
                        cPtr = Queue[i];
                        cout << cPtr->source << "->";
                        cPtr->capacity += min;//Update capacity
						//
						residualGraph[cPtr->destination][cPtr->source].capacity -= min;
                    }
                    cout << cPtr->destination << " : " << min << endl;
                    min = INT_MAX;
                    Queue.pop_back();
                }
                else
                    capacityExceed = false;
                continue;
            }
        }

		for(int i = numberOfNodes - 1; i >= current.source; i--)//Branch neighbour
        {
            if(graphMatrix[current.source - 1][i].capacity - residualGraph[current.source - 1][i].capacity > 0)
            {
                Stack.push_back(graphMatrix[current.source - 1][i]);
            }
        }
    }

	Queue.clear();
	DeleteResidualGraph();

    return flow;
}

void Graph::CreateResidualGraph()
{
	residualGraph = new Cell*[numberOfNodes];
    for(int i = 0; i < numberOfNodes; i++)
        residualGraph[i] = new Cell[numberOfNodes];

	for(int i = 0; i < numberOfNodes; i++)
	{
		for(int j = 0; j < numberOfNodes; j++)
		{
			if(graphMatrix[i][j].source != 0)//Is there a node
			{
				residualGraph[i][j].source = graphMatrix[i][j].source;
				residualGraph[i][j].destination = graphMatrix[i][j].destination;
			}
		}
	}
}

void Graph::DeleteResidualGraph()
{
	for(int i = 0; i < numberOfNodes; i++)
        delete[] residualGraph[i];
    delete[] residualGraph;
}

void Graph::UpdateCapacity(char* fileName)
{
	ifstream inputFile(fileName);
    Cell newData;
    deque<Cell> list;

    if(!inputFile.is_open())
        throw "File could not be opened.";

    while(!inputFile.eof())
    {
        inputFile >> newData.source >> newData.destination >> newData.capacity;
		residualGraph[newData.source - 1][newData.destination - 1].capacity = newData.capacity;
		residualGraph[newData.destination - 1][newData.source - 1] = newData.switchSourceAndDestination();
    }
}


Graph::~Graph()
{
    for(int i = 0; i < numberOfNodes; i++)
    {
        delete[] graphMatrix[i];
        delete[] residualGraph[i];
    }
    delete[] graphMatrix;
    delete[] residualGraph;
}
