#ifndef SCANNER_H
#define SCANNER_H

#include <string>

using namespace std;

class Scanner
{
    public:
        Scanner(string input);
        string getNextToken();
        string findNextToken();
    private:
        int index;
        string nextToken;
        string input;

};

#endif // SCANNER_H
