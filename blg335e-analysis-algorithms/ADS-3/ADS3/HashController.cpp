#include "HashController.h"
#include <iostream>
#include <fstream>

using namespace std;

void HashController::insert(HashTable& hTable, string fileName)
{
    int numberOfCollisions = 0;

    ifstream inputFile(fileName.data());

    if(inputFile.is_open())
    {
        long nextKey;
        while(!inputFile.eof()){
            inputFile >> nextKey;

            for(long i = 0; i < hTable.getCapacity(); i++)
            {
                int index = hTable.findIndex(nextKey, i);
                if(hTable.getValue(index) == -1)
                {
                    hTable.setValue(nextKey, index);
                    break;
                }
                else
                    numberOfCollisions++;
            }
        }

        inputFile.close();

        cout << "Number of collisions when insert operation: " << numberOfCollisions << endl;
    }
    else
        cout << fileName << " could not be opened!" << endl;

}

void HashController::search(HashTable& hTable, string fileName)
{
    int numberOfCollisions = 0;

    ifstream inputFile(fileName.data());

    if(inputFile.is_open())
    {
        long nextKey;
        while(!inputFile.eof()){
            inputFile >> nextKey;

            for(long i = 0; i < hTable.getCapacity(); i++)
            {
                int index = hTable.findIndex(nextKey, i);
                if(hTable.getValue(index) != -1 && hTable.getValue(index) == nextKey)//No collision, slot is full with searched key
                    break;
                else if(hTable.getValue(index) != -1)//Collision, continue to search
                    numberOfCollisions++;
                else//Slot is empty
                    break;
            }
        }

        inputFile.close();

        cout << "Number of collisions when search operation: " << numberOfCollisions << endl;
    }
    else
        cout << fileName << " could not be opened!" << endl;
}
