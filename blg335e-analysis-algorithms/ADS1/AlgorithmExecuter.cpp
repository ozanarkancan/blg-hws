#include "AlgorithmExecuter.h"
#include <iostream>

using namespace std;

AlgorithmExecuter::AlgorithmExecuter(const Location& rhs)
{
    this->target = Location(rhs);
}

//Executes necessary functions by given algorithm type
vector<Location> AlgorithmExecuter::executeAlgorithm(vector<Location>& locations, unsigned k, char algorithmType)
{
    vector<Location> result = vector<Location>();
    vector<Location> sorted = vector<Location>();

    switch(algorithmType)
    {
    case 'M'://MergeSort
        sorted = mergeSort(locations);
        for(unsigned i = 0; i < k; i++)
            result.push_back(sorted[i]);
        break;
    case 'I'://InsertionSort
        insertionSort(locations);
        for(unsigned i = 0; i < k; i++)
            result.push_back(locations[i]);
        break;
    case 'L'://LinearSearch
        result = linearSearch(locations, k);
        break;
    default:
        cout << "Wrong algorithm type" << endl;
    }
    return result;
}

vector<Location> AlgorithmExecuter::mergeSort(vector<Location>& locations)
{
    if(locations.size() == 1)
        return locations;

    vector<Location> left(locations.begin(), locations.begin() + (locations.size() / 2));
    vector<Location> right(locations.begin() + (locations.size() / 2), locations.end());

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

vector<Location> AlgorithmExecuter::merge(vector<Location>& left, vector<Location>& right)
{
    vector<Location> result;

    unsigned leftIt = 0, rightIt = 0;

    while(leftIt < left.size() && rightIt < right.size())
    {
        if(this->target.getDistance(left[leftIt]) < this->target.getDistance(right[rightIt]))
        {
            result.push_back(left[leftIt]);
            leftIt++;
        }
        else
        {
            result.push_back(right[rightIt]);
            rightIt++;
        }
    }

    while(leftIt < left.size())
    {
        result.push_back(left[leftIt]);
        leftIt++;
    }

    while(rightIt < right.size())
    {
        result.push_back(right[rightIt]);
        rightIt++;
    }

    return result;
}

void AlgorithmExecuter::insertionSort(vector<Location>& locations)
{
    for(unsigned i = 1; i < locations.size(); i++)
    {
        for(unsigned j = i; j > 0 && target.getDistance(locations[j]) < target.getDistance(locations[j - 1]); j--)
        {
            Location temp = locations[j];
            locations[j] = locations[j - 1];
            locations[j - 1] = temp;
        }
    }
}

vector<Location> AlgorithmExecuter::linearSearch(vector<Location>& locations, unsigned k)
{
    vector<Location> result = vector<Location>();
    for(unsigned i = 0; i < locations.size(); i++)
    {
        bool added = false;//Hold a flag for k sized candidate list
        for(unsigned j = 0; j < k && j < result.size(); j++)
        {
            if(target.getDistance(locations[i]) < target.getDistance(result[j]))
            {
                result.insert(result.begin() + j, locations[i]);
                added = true;

                if(result.size() > k)//If size of list greater than k remove last location from candidates
                    result.erase(result.end());
                break;
            }
        }

        if(added)
            added = false;
        else if(result.size() < k)//Add location to end of candidate list
            result.push_back(locations[i]);
    }

    return result;
}
