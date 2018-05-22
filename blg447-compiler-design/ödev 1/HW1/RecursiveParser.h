#ifndef RECURSIVEPARSER_H
#define RECURSIVEPARSER_H

#include <string>

using namespace std;

class RecursiveParser
{
    public:
        void parseInput(string input);
    private:
        int index;
        string input;
        char nextToken;

        void parseProg();
        void parseDeyimler();
        void parseDeyim();
        void parseExp();
        void parseExpt();
        char getNextToken();
        void parseError();

};

#endif // RECURSIVEPARSER_H
