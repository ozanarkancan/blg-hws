/*
* Course: BLG381E
* Homework #1
*
* Ozan Arkan CAN
* 040090573
*/



#include <iostream>
#include <cstdlib>
#include "nQueen.h"
#include <ctime>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        nQueen solver(atoi(argv[1]));
        clock_t tStart, tFinish;
        tStart = clock();
        solver.permutation(solver.getList(), 0, atoi(argv[1]) - 1);
        tFinish = clock();
        cout << "Number of inputs: " << atoi(argv[1]) << endl;
        cout << "Running time: " << tFinish - tStart << " miliseconds" << endl;
        solver.showResult();
        cout << endl;
    }
    else
    {
        cout << "You must execute this program with parameter n\nhomework1.exe 8" << endl;
    }
    return 0;
}
