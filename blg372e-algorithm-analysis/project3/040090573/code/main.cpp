#include <iostream>
#include <stdlib.h>
#include "Graph.h"
#include <fstream>

using namespace std;

deque<Cell> getNetwork(char*, unsigned short int&);
void menu();

int main(int argc, char* argv[])
{
    if(argc == 3)
    {
        unsigned short int option = -1;
        unsigned short int numberOfNodes = 0;
        deque<Cell> infoFromFile;
        int flow;

        try
        {
            infoFromFile = getNetwork(argv[1], numberOfNodes); //Parse file and get network
            Graph* graph = new Graph(numberOfNodes, infoFromFile);

            while(option != 3)
            {
                menu(); // Show menu to user
                cin >> option;
				cout << endl;
                switch(option)
                {
                    case 1:
                        cout << "Traces and capacities:" << endl << endl;
						graph->CreateResidualGraph();
                        flow = graph->MaxFlow();
                        cout << endl << "Maximum flow:\t" << flow << endl;
                        break;
                    case 2:
						graph->CreateResidualGraph();
						graph->UpdateCapacity(argv[2]);
						flow = graph->IsMaxFlow();
                        cout << endl << "Is Maximum flow?:\t";
                        if(flow = 0)
                            cout << "Yes" << endl;
                        else
                            cout << "No" << endl;
                        break;
                    case 3:
                        cout << "Program was terminated." << endl;
                        break;
                    default:
                        cout << "Invalid choice." << endl << endl;
                }
        }

        return 0;
        }
        catch(char* exception)
        {
            cout << exception << endl;
            return 1;
        }
    }
    else //Inform user about wrong call
    {
        cout << "Wrong program call!" << endl;
        cout << "Program must be executed with this configuration:" << endl;
        cout << ".\\main file_name1 file_name2" << endl;
        return 1;
    }
}

deque<Cell> getNetwork(char* fileName, unsigned short int& numberOfNodes)
{
    ifstream inputFile(fileName);
    Cell* newData;
    deque<Cell> list;

    if(!inputFile.is_open())
        throw "File could not be opened.";

    while(!inputFile.eof())
    {
        newData = new Cell();
        inputFile >> newData->source >> newData->destination >> newData->capacity;

        if(newData->source > numberOfNodes)
            numberOfNodes = newData->source;
        if(newData->destination > numberOfNodes)
            numberOfNodes = newData->destination;

        list.push_back(*newData);
    }

    return list;
}

void menu()//List of options
{
    cout << endl;
    cout << "1. Mission 1" << endl;
    cout << "2. Mission 2" << endl;
    cout << "3. Exit" << endl;
    cout << "your choice: ";
}
