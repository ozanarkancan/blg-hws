#include "Cell.h"

Cell::Cell()
{
    destination = 0;
    source = 0;
    capacity = 0;
}

Cell Cell::switchSourceAndDestination()
{
    Cell tmp;

    tmp.source = destination;
    tmp.destination = source;
    tmp.capacity = capacity;

    return tmp;
}

bool Cell::operator==(const Cell& c) const
{
    return (this->source == c.source && this->destination == c.destination && this->capacity == c.capacity);
}

