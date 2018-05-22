#include <iostream>
#include "Heap.h"
#include "Simulator.h"
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cout << "Wrong program call." << endl;
        return 1;
    }
    else
    {
        Simulator simulator;

        try
        {
            simulator.simulate(atoi(argv[1]), atof(argv[2]));
        }
        catch(const char* msg)
        {
            cout << msg << endl;
        }

        return 0;
    }
}
