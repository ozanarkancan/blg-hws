#include "Location.h"

#include <cmath>

Location::Location()
{
    this->city = "";
    this->latitude = 0;
    this->longitude = 0;
}

Location::Location(string city, float latitude, float longitude)
{
    this->city.assign(city);
    this->latitude = latitude;
    this->longitude = longitude;
}

//Copy constructor
Location::Location(const Location& rhs)
{
    this->city.assign(rhs.getCity());
    this->latitude = rhs.getLatitude();
    this->longitude = rhs.getLongitude();
}

string Location::getCity() const
{
    return this->city;
}

float Location::getLatitude() const
{
    return this->latitude;
}
float Location::getLongitude() const
{
    return this->longitude;
}

//Calculates difference between this location and target location
float Location::getDistance(const Location& rhs) const
{
    float dlon = rhs.getLongitude() - this->getLongitude();
    float dlat = rhs.getLatitude() - this->getLatitude();
    float a = sin(dlat * 0.017453292519943 / 2) * sin(dlat * 0.017453292519943 / 2)
        + cos(this->getLatitude() * 0.017453292519943) * cos(rhs.getLatitude() * 0.017453292519943)
        * sin(dlon * 0.017453292519943 / 2) * sin(dlon * 0.017453292519943 / 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    float d = 6373 * c;

    return d;
}
