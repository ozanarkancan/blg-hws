#include "HashTable.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

HashTable::HashTable(int m, int hashType)
{
    this->hashSize = m;
    this->hashType = hashType;

    this->table = new int[m];

    for(int i = 0; i < m; i++)
        this->table[i] = -1;

    if(hashType == 2)
    {
        srand(time(NULL));
        aj = new long[3];
        for(int i = 0; i < 3; i++)
            aj[i] = rand() % m;
    }
}

HashTable::~HashTable()
{
    delete[] this->table;
    if(hashType == 2)
        delete[] this->aj;
}

int HashTable::linearProbing(long k, int i)
{
    return (k + i) % hashSize;
}

int HashTable::doubleProbing(long k, int i)
{
    long h1 = k % hashSize;
    long h2 = 1 + (k % (hashSize - 1));

    return (h1 + i * h2) % hashSize;
}

int HashTable::universalHashing(long k, int i)
{
    long kj[3];
    kj[2] = k % 1000;
    k = k / 1000;

    kj[1] = k % 1000;
    k = k / 1000;

    kj[0] = k % 1000;

    long total = 0;

    for(long j = 0; j < 3; j++)
        total += aj[j] * kj[j];

    return (total + i) % hashSize;
}

int HashTable::findIndex(long k, int i)
{
    switch(hashType)
    {
    case 0:
        return linearProbing(k, i);
    case 1:
        return doubleProbing(k, i);
    case 2:
        return universalHashing(k, i);
    default:
        return linearProbing(k, i);
    }
}

void HashTable::setValue(long value, int index)
{
    table[index] = value;
}

int HashTable::getCapacity()
{
    return hashSize;
}

long HashTable::getValue(int index)
{
    return table[index];
}
