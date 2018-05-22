#include <iostream>
#include "CombinatorialSolution.h"
#include "PascalTriangleSolution.h"
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cout << "Wrong program call." << endl;
        cout << "./programName <valueOfN> <valueOfK>"<< endl;
    }
    else
    {
        unsigned int maxN = atoi(argv[1]);
        unsigned int k = atoi(argv[2]);

        CombinatorialSolution cSol;
        cSol.solve(maxN, k);
        cSol.solveEfficient(maxN, k);
        PascalTriangleSolution pSol;
        pSol.solve(maxN, k);
    }
    return 0;
}
