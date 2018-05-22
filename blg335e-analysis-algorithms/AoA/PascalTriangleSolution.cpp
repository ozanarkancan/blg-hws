#include "PascalTriangleSolution.h"
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

BigUnsignedInt PascalTriangleSolution::getPascalValue(unsigned int i, unsigned int j)
{
    if(j == 0 || i == j)
        return BigUnsignedInt((unsigned int) 1);//Return 1
    else
        return getPascalValue(i - 1, j - 1) + getPascalValue(i - 1, j);//Add necessary values from previous level
}

void PascalTriangleSolution::solve(unsigned int maxN, unsigned int k)
{
    ofstream output;//ofstream variable to write file
    struct timeval startingTime, finishingTime;//Variables to evaluate running time
    long totalTime, seconds, useconds;

    output.open("pascal.txt");//open file

    gettimeofday(&startingTime, NULL);//Start

    deque<BigUnsignedInt> previousValues;
    for(unsigned int i = 0; i <= maxN; i++)
    {
        for(unsigned int j = 0; j <= i; j++)
        {
            unsigned int min = (i - j > j) ? j : (i - j);
            BigUnsignedInt pascalTriangleValue = getPascalValue(i, min);
            output << i << " " << j << " ";
            if(i == maxN && j == k)
                output << pascalTriangleValue << endl;
            else
                output << pascalTriangleValue.getBinaryLength() << endl;
        }
    }
    gettimeofday(&finishingTime, NULL);//End
    seconds  = finishingTime.tv_sec  - startingTime.tv_sec;
    useconds = finishingTime.tv_usec - startingTime.tv_usec;
    totalTime = ((seconds) * 1000 + useconds/1000.0);//Calculate microseconds
    cout << "Running time of pascal triangle solution: " << totalTime << " microseconds" << endl;
    output.close();
}
