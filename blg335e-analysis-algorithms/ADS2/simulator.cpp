#include "simulator.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Heap.h"

using namespace std;

void Simulator::simulate(int m, float p)
{
    srand(time(NULL));

    ifstream bidFile("bids.txt");

    if(bidFile.is_open())
    {
        clock_t startTime, endTime;

        Heap priorityQueue(m);

        int numberOfNewBids = 0;
        int numberOfUpdates = 0;
        int orderOfAuction = 0;

        double winnerKeys[m / 100];//Additional variable to hold winners because of time complexity of showing input in loop

        startTime = clock();

        for(int i = 1; i <= m; i++)
        {
            if(isUpdateOperation(p) && priorityQueue.getHeapSize() != 0)//Check wheather heap is empty
            {
                int indexOfRandomInstance = selectRandomInstance(priorityQueue.getHeapSize());//Select a random instance
                double currKey = priorityQueue.getKey(indexOfRandomInstance);
                priorityQueue.HEAP_INCREASE_KEY(indexOfRandomInstance, currKey * 1.25);//Update selected instance
                numberOfUpdates++;
            }
            else
            {
                double newBid;
                bidFile >> newBid;//Read new bid
                priorityQueue.MAX_HEAP_INSERT(newBid);
                numberOfNewBids++;
            }

            if((numberOfUpdates + numberOfNewBids) % 100 == 0)
            {
                double winnerKey = priorityQueue.HEAP_EXTRACT_MAX();
                //cout << "The bid value of " << orderOfAuction << ". auction winner: " << winnerKey << endl;
                winnerKeys[orderOfAuction] = winnerKey;//Add winner to list to show after all operations are completed
                orderOfAuction++;
            }
        }

        endTime = clock();

        for(int i = 0; i < orderOfAuction; i++)
            cout << "The bid value of " << i + 1 << ". auction winner: " << winnerKeys[i] << endl;

        cout << endl;
        cout << "Number of new bids: " << numberOfNewBids << endl;
        cout << "Number of updates: " << numberOfUpdates << endl << endl;


        cout << "Running time: " << (float)(endTime - startTime) * 1000 / CLOCKS_PER_SEC << " ms" << endl << endl;

        bidFile.close();
    }
    else
        throw "Bid file could not be opened.";
}

int Simulator::selectRandomInstance(int numberOfInstances)
{
    return rand() % numberOfInstances;
}

bool Simulator::isUpdateOperation(float updateProbability)
{
    bool result;
    int randomNumber = rand() % 1000;

    result = (float)randomNumber < 1000 * updateProbability;
    return result;
}
