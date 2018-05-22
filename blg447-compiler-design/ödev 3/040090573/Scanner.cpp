#include "Scanner.h"

using namespace std;

Scanner::Scanner(string input)
{
    this->input = input;
    index = 0;
}

string Scanner::getNextToken()
{
    return nextToken;
}

string Scanner::findNextToken()
{
    string next = "";

    if(index >= input.size())
        throw "Girdi sonuna ulasildi. Gecersiz ayristirma!";
    else if(input[index] == '[')
        next = "[";
    else if(input[index] == ']')
        next = "]";
    else if(input[index] == '(')
        next = "(";
    else if(input[index] == ')')
        next = ")";
    else if(input[index] == '=')
        next = "=";
    else if(input[index] == ';')
        next = ";";
    else if(input[index] == '$')
        next = "$";
    else if(input[index] >= 97 && input[index] <= 122)
        next = "id";
    else
        throw "Gecersiz girdi hatasi!";

    index++;

    return next;
}
