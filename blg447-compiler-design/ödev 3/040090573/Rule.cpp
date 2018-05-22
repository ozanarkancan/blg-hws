#include "Rule.h"

Rule::Rule()
{
    leftSide = "";
    rightSide = "";
}

Rule::Rule(string leftSide, string rightSide, int id)
{
    this->leftSide = leftSide;
    this->rightSide = rightSide;
    this->id = id;
}

Rule::Rule(string leftSide, string rightSide, int id, int num)
{
    this->leftSide = leftSide;
    this->rightSide = rightSide;
    this->id = id;
    this->numberOfSymbolsAtRightSide = num;
}

Rule::Rule(const Rule& rhs)
{
    this->leftSide = string(rhs.leftSide);
    this->rightSide = string(rhs.rightSide);
    this->id = rhs.id;
    this->numberOfSymbolsAtRightSide = rhs.numberOfSymbolsAtRightSide;
}

bool Rule::operator==(const Rule rhs) const
{
    return this->leftSide.compare(rhs.leftSide) == 0 && this->rightSide.compare(rhs.rightSide) == 0;
}

bool Rule::operator!=(const Rule rhs) const
{
    return !(*this == rhs);
}
