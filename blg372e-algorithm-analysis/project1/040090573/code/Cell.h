#ifndef CELL_H
#define CELL_H

using namespace std;

class Cell
{
    public:
        Cell();
        Cell switchSourceAndDestination();// Swaps source and destination and return new cell object.
        unsigned short int source;
        unsigned short int destination;
        unsigned short int timestamp;
        bool operator==(const Cell&) const;// operator == overloading for comparison in stack
};

#endif // CELL_H
