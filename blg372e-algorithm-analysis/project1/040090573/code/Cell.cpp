#include "Cell.h"

Cell::Cell()
{
    destination = 0;
    source = 0;
    timestamp = 0;
}

Cell Cell::switchSourceAndDestination()
{
    Cell tmp;

    tmp.source = destination;
    tmp.destination = source;
    tmp.timestamp = timestamp;

    return tmp;
}

bool Cell::operator==(const Cell& c) const
{
    return (this->source == c.source && this->destination == c.destination && this->timestamp == c.timestamp);
}

