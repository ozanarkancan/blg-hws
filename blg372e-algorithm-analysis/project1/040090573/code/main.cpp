#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Graph.h"

using namespace std;

deque<Cell> getCommunicationInfo(char*, unsigned short int&, unsigned short int);
void menu();

int main(int argc, char* argv[])
{
    if(argc == 4)
    {
        unsigned short int option = -1, computerNo;
        unsigned short int firstInjectedComputer = atoi(argv[2]);
        unsigned short int firstInjectionTime = atoi(argv[3]);
        unsigned short int numberOfNodes = 0;
        deque<Cell> infoFromFile;

        try
        {
            infoFromFile = getCommunicationInfo(argv[1], numberOfNodes, firstInjectionTime); //Parse file and get communication network
            Graph* graph = new Graph(firstInjectedComputer, firstInjectionTime, numberOfNodes, infoFromFile);
            graph->DetectAllPath();

            while(option != 3)
            {
                menu(); // Show menu to user
                cin >> option;
                switch(option)
                {
                    case 1:
                        graph->PrintAllInjectedComputer();
                        break;
                    case 2:
                        cout << "Please enter the no of computer: ";
                        cin >> computerNo;

                        if(computerNo > numberOfNodes || computerNo < 1)
                        {
                            cout << "There is no computer with no " << computerNo << endl;
                            break;
                        }

                        cout << "Is infected? ";
                        graph->CheckComputerIsInjected(computerNo);
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
        cout << ".\\main \"file_name\" computer_no timestamp" << endl;
        return 1;
    }
}

deque<Cell> getCommunicationInfo(char* fileName, unsigned short int& numberOfNodes, unsigned short int firstInjectionTime)
{
    ifstream inputFile(fileName);
    Cell* newData;
    deque<Cell> list;

    if(!inputFile.is_open())
        throw "File could not be opened.";

    while(!inputFile.eof())
    {
        newData = new Cell();
        inputFile >> newData->source >> newData->destination >> newData->timestamp;

        if(newData->timestamp >= firstInjectionTime)//Eliminate communication between two computers that they communicate before first injection time
            list.push_back(*newData);

        if(newData->source > numberOfNodes)
            numberOfNodes = newData->source;
        if(newData->destination > numberOfNodes)
            numberOfNodes = newData->destination;
    }

    return list;
}

void menu()//List of options
{
    cout << endl;
    cout << "1. List the computers which can be infected?" << endl;
    cout << "2. Enter a computer no in order to test if it is infected?" << endl;
    cout << "3. Exit" << endl;
    cout << "your choice: ";
}
