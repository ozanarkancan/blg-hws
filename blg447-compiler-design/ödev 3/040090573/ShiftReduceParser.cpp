#include "ShiftReduceParser.h"
#include <iostream>
#include <stdlib.h>
#include "Cell.h"
#include "Scanner.h"

using namespace std;

ShiftReduceParser::ShiftReduceParser()
{
    pt.generateTable();
    pt.printTable();
}

ShiftReduceParser::~ShiftReduceParser()
{
    //dtor
}

void ShiftReduceParser::parseInput(string input)
{
    Scanner scanner(input);

    parseStack.push("0");
    string token = scanner.findNextToken();

    while(true)
    {
        string s = parseStack.top();
        int state = atoi(s.data());

        Cell cell = pt.getCell(state, token);

        cout << "Durum: " << s << endl;
        cout << "Sozcuk: " << token << endl;
        cout << "Karar: " << cell.action << endl;
        cout << "NO: " << cell.no << endl << endl;

        if(cell.action.compare("r") == 0)
        {
            Rule r = pt.getGrammar().ruleList[cell.no];
            int numOfSymbols = r.numberOfSymbolsAtRightSide;

            for(int i = 0; i < 2 * numOfSymbols; i++)//Türetimin sað tarafýndaki sembol sayýsý kadar yýðýndan çek
                parseStack.pop();

            s = parseStack.top();
            state = atoi(s.data());

            parseStack.push(r.leftSide);
            cell = pt.getCell(state, r.leftSide);
            char buff[1];
            itoa(cell.no, buff, 10);
            parseStack.push(buff);
        }
        else if(cell.action.compare("s") == 0)
        {
            parseStack.push(token);
            char buff[1];
            itoa(cell.no, buff, 10);
            parseStack.push(buff);
            token = scanner.findNextToken();
        }
        else if(cell.isAcceptance && token.compare("$") == 0)
        {
            cout << "Ayristirma islemi basarili." << endl;
            break;
        }
        else
        {
            cout << "Ayristirma hatasi!" << endl;
            break;
        }
    }
}
