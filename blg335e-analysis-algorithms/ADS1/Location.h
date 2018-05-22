#ifndef LOCATION_H
#define LOCATION_H

#include <string>

using namespace std;

class Location
{
    public:
        Location();
        Location(string city, float latitude, float longitude);
        Location(const Location& rhs);
        string getCity() const;
        float getLatitude() const;
        float getLongitude() const;
        float getDistance(const Location& rhs) const;//Calculates difference between this location and target location

    private:
        string city;
        float latitude;
        float longitude;
};

#endif // LOCATION_H
