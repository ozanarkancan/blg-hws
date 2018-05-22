#include <iostream>
#include "ShiftReduceParser.h"

using namespace std;

int main()
{
    ShiftReduceParser parser;
    try{
        parser.parseInput("a[e]=b$$");
    }
    catch(const char* msg)
    {
        cout << msg << endl;
    }

    return 0;
}
