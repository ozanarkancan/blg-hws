#include "RecursiveParser.h"
#include <iostream>

using namespace std;

void RecursiveParser::parseInput(string input)
{
    this->input = input;
    this->index = 0;
    try
    {
        this->nextToken = getNextToken();
        parseProg();

        cout << endl;
        cout << "Ayristirma basarili..." << endl;
    }
    catch(const char* msg)
    {
        cout << endl;
        cout << msg << endl;
        cout << "Ayristirma basarisiz..." << endl;
    }
}

void RecursiveParser::parseProg()
{
    cout << "parseProg cagrildi" << endl;
    if(nextToken == '{')
    {
        nextToken = getNextToken();
        parseDeyimler();
        if(nextToken != '}')
            throw "parseProg cagrisinda ayristirma hatasi...";
        nextToken = getNextToken();
        if(nextToken != '$')
            throw "parseProg cagrisinda ayristirma hatasi...";
        return;
    }
    else
        throw "parseProg cagrisinda ayristirma hatasi...";
}

void RecursiveParser::parseDeyimler()
{
    cout << "parseDeyimler cagrildi" << endl;
    switch(nextToken)
    {
    case 'V':
        parseDeyim();
        parseDeyimler();
        return;
    case '}':
        return;
    case 'I':
        parseDeyim();
        parseDeyimler();
        return;
    default:
        throw "parseDeyimler cagrisinda ayristirma hatasi...";
    }
}

void RecursiveParser::parseDeyim()
{
    cout << "parseDeyim cagrildi" << endl;
    switch(nextToken)
    {
    case 'V':
        nextToken = getNextToken();
        if(nextToken != '=')
            throw "parseDeyim cagrisinda ayristirma hatasi...";
        nextToken = getNextToken();
        parseExp();
        if(nextToken != ';')
            throw "parseDeyim cagrisinda ayristirma hatasi...";
        nextToken = getNextToken();
        return;
    case 'I':
        nextToken = getNextToken();
        if(nextToken != '(')
            throw "parseDeyim cagrisinda ayristirma hatasi...";
            nextToken = getNextToken();
        parseExp();
        if(nextToken != ')')
            throw "parseDeyim cagrisinda ayristirma hatasi...";
        nextToken = getNextToken();
        parseDeyim();
        return;
    default:
        throw "parseDeyim cagrisinda ayristirma hatasi...";
    }
}

void RecursiveParser::parseExp()
{
    cout << "parseExp cagrildi" << endl;

    if(nextToken == 'V')
    {
        nextToken = getNextToken();
        parseExpt();
        return;
    }
    else
        throw "parseExp cagrisinda ayristirma hatasi...";
}

void RecursiveParser::parseExpt()
{
    cout << "parseExpt cagrildi" << endl;
    switch(nextToken)
    {
    case '-':
        nextToken = getNextToken();
        parseExp();
        return;
    case '+':
        nextToken = getNextToken();
        parseExp();
        return;
    case ')':
        return;
    case ';':
        return;
    default:
        throw "parseExpt cagrisinda ayristirma hatasi...";
    }
}

char RecursiveParser::getNextToken()
{
    if(this->index >= this->input.size())
        throw "Gecersiz girdi bulunmakta...";

    char curr = this->input[index];

    //-,+,(,),{,},=,;,$
    if(curr == 45 || curr == 43 || curr == 40 || curr == 41
       || curr == 123 || curr == 125 || curr == 61|| curr == 59 || curr == 36)
    {
        this->index++;
        return curr;
    }
    else if(curr == 105)//Geçerli harf i ise sýradaki sözcük if mi kontrol et
    {
        if(index < this->input.size() - 1)
        {
            if(this->input[index + 1] == 102)
            {
                this->index = this->index + 2;
                return 'I';//I if sözcüðünü temsil ediyor
            }
            else
            {
                this->index++;
                return curr;
            }
        }
        else
        {
            this->index++;
            return curr;
        }
    }
    else if(curr >= 97 && curr <= 122)//Geçerli harf küçük harfse bir deðiþken ismi
    {
        this->index++;
        return 'V';//V herhangi bir deðiþken ismini temsil ediyor
    }
    else//Hatalý girdi var
        throw "Gecersiz girdi bulunmakta...";
}
