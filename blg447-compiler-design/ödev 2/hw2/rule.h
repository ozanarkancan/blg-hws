#ifndef RULE_H
#define RULE_H

#include <string>

using namespace std;

class Rule
{
    public:
        Rule();
        Rule(string leftSide, string rightSide, int id);
        Rule(const Rule& rhs);
        string leftSide;
        string rightSide;
        int id;
        bool operator==(const Rule rhs) const;
        bool operator!=(const Rule rhs) const;
};

#endif // RULE_H
