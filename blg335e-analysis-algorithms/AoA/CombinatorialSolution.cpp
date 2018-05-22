#include "CombinatorialSolution.h"
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;


//Make combination n! / (k! * (n-k)!)
BigUnsignedInt CombinatorialSolution::makeCombination(unsigned int n, unsigned int k)
{
    unsigned int denominator = (n - k > k) ? k : (n - k);//min (k, n - k)

    BigUnsignedInt numerator = BigUnsignedInt((unsigned int) 1);
    for(int i = n; i > n - denominator; i--)//Make n * (n - 1) * ... * (n - denominator)
        numerator = numerator * (unsigned int)i;
    BigUnsignedInt result = numerator / factorial(denominator);
    return result;
}

BigUnsignedInt CombinatorialSolution::factorial(unsigned int n)//Find n!
{
    BigUnsignedInt fact = BigUnsignedInt((unsigned int)1);
    for(unsigned int i = 2; i <= n; i++)
        fact = fact * i;
    return fact;
}

void CombinatorialSolution::solve(unsigned int maxN, unsigned int k)
{
    ofstream output;//ofstream variable to write file
    struct timeval startingTime, finishingTime;//Variables to evaluate running time
    long totalTime, seconds, useconds;

    output.open("combinatorial.txt");//open file

    gettimeofday(&startingTime, NULL);//Start

    for(unsigned int i = 0; i <= maxN; i++)
    {
        for(unsigned int j = 0; j <= i; j++)
        {
            BigUnsignedInt combination = makeCombination(i, j);
            output << i << " " << j << " ";
            if(i == maxN && j == k)
                output << combination << endl;
            else
                output << combination.getBinaryLength() << endl;
        }
    }
    gettimeofday(&finishingTime, NULL);//End
    seconds  = finishingTime.tv_sec  - startingTime.tv_sec;
    useconds = finishingTime.tv_usec - startingTime.tv_usec;
    totalTime = ((seconds) * 1000 + useconds/1000.0);//Calculate microseconds
    cout << "Running time of combinatorial solution: " << totalTime << " microseconds" << endl;
    output.close();//Close file
}

//Section for solution to problem using Karatsuba and division algorithm

BigUnsignedInt CombinatorialSolution::factorialEfficient(unsigned int n)//Find n!
{
    BigUnsignedInt fact = BigUnsignedInt((unsigned int)1);
    for(unsigned int i = 2; i <= n; i++)
        fact = fact.karatsuba(BigUnsignedInt(i));//Use karatsube
    return fact;
}

//Make combination n! / (k! * (n-k)!)
BigUnsignedInt CombinatorialSolution::makeCombinationEfficient(unsigned int n, unsigned int k)
{
    unsigned int denominator = (n - k > k) ? k : (n - k);//min (k, n - k)

    BigUnsignedInt numerator = BigUnsignedInt((unsigned int) 1);
    for(int i = n; i > n - denominator; i--)//Make n * (n - 1) * ... * (n - denominator)
        numerator = numerator.karatsuba(BigUnsignedInt((unsigned int)i));

    BigUnsignedInt result = numerator.fastDivision(factorial(denominator));
    return result;
}

void CombinatorialSolution::solveEfficient(unsigned int maxN, unsigned int k)
{
    ofstream output;//ofstream variable to write file
    struct timeval startingTime, finishingTime;//Variables to evaluate running time
    long totalTime, seconds, useconds;

    output.open("combinatorialEfficient.txt");//open file

    gettimeofday(&startingTime, NULL);//Start

    for(unsigned int i = 0; i <= maxN; i++)
    {
        for(unsigned int j = 0; j <= i; j++)
        {
            BigUnsignedInt combination = makeCombinationEfficient(i, j);
            output << i << " " << j << " ";
            if(i == maxN && j == k)
                output << combination << endl;
            else
                output << combination.getBinaryLength() << endl;
        }
    }
    gettimeofday(&finishingTime, NULL);//End
    seconds  = finishingTime.tv_sec  - startingTime.tv_sec;
    useconds = finishingTime.tv_usec - startingTime.tv_usec;
    totalTime = ((seconds) * 1000 + useconds/1000.0);//Calculate microseconds
    cout << "Running time of efficient combinatorial solution: " << totalTime << " microseconds" << endl;
    output.close();//Close file
}
