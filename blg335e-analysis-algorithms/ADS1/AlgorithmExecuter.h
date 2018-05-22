#ifndef ALGORITHMEXECUTER_H
#define ALGORITHMEXECUTER_H

#include "Location.h"
#include <vector>

using namespace std;

class AlgorithmExecuter
{
    public:
        AlgorithmExecuter(const Location& target);
        /*
        Algorithm type:

        'M' :MergeSort
        'I' :InsertionSort
        'L' :LinearSearch

        */
        vector<Location> executeAlgorithm(vector<Location>& locations, unsigned k, char algorithmType);
    private:
        Location target;//Target Location
        vector<Location> mergeSort(vector<Location>& locations);
        vector<Location> merge(vector<Location>& left, vector<Location>& right);
        void insertionSort(vector<Location>& locations);
        vector<Location> linearSearch(vector<Location>& locations, unsigned k);

};

#endif // ALGORITHMEXECUTER_H
