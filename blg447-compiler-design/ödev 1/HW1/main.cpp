#include <iostream>
#include "RecursiveParser.h"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cout << "Yanlis program cagrisi. ./040090573_o1 <input> þeklinde calistirin." << endl;
        return 1;
    }

    string input = argv[1];

    RecursiveParser parser;
    parser.parseInput(input);
    return 0;
}
