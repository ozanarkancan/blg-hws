#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

void initializeTable(int m, int hashType);
int linearProbing(long k, int i);
int doubleProbing(long k, int i);
int universalHashing(long k, int i);
int findIndex(long k, int i);
void setValue(long value, int index);
int getCapacity();
long getValue(int index);
void insert(string fileName);
void search(string fileName);

int hashSize;
int hashType;
int* table;
long* aj;

int main()
{
    cout << "***Linear probing***" << endl;
    cout << "\nm: 1327\n" << endl;

    initializeTable(1327, 0);

    insert("insert.txt");
    search("search.txt");

    cout << "\nm: 2657\n" << endl;

    initializeTable(2657, 0);

    insert("insert.txt");
    search("search.txt");

    cout << "\n***Double probing***" << endl;
    cout << "\nm: 1327\n" << endl;

    initializeTable(1327, 1);

    insert("insert.txt");
    search("search.txt");

    cout << "\nm: 2657\n" << endl;

    initializeTable(2657, 1);

    insert("insert.txt");
    search("search.txt");

    cout << "\n***Universal Hashing***" << endl;
    cout << "\nm: 1327\n" << endl;

    initializeTable(1327, 2);

    insert("insert.txt");
    search("search.txt");

    cout << "\nm: 2657\n" << endl;

    initializeTable(2657, 2);

    insert("insert.txt");
    search("search.txt");


    return 0;
}

void initializeTable(int m, int hashType)
{
    hashSize = m;
    hashType = hashType;

    table = new int[m];

    for(int i = 0; i < m; i++)
        table[i] = -1;

    if(hashType == 2)
    {
        srand(time(NULL));
        aj = new long[3];
        for(int i = 0; i < 3; i++)
            aj[i] = rand() % m;
    }
}

int linearProbing(long k, int i)
{
    return (k + i) % hashSize;
}

int doubleProbing(long k, int i)
{
    long h1 = k % hashSize;
    long h2 = 1 + (k % (hashSize - 1));

    return (h1 + i * h2) % hashSize;
}

int universalHashing(long k, int i)
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

int findIndex(long k, int i)
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

void setValue(long value, int index)
{
    table[index] = value;
}

int getCapacity()
{
    return hashSize;
}

long getValue(int index)
{
    return table[index];
}

void insert(string fileName)
{
    int numberOfCollisions = 0;

    ifstream inputFile(fileName.data());

    if(inputFile.is_open())
    {
        long nextKey;
        while(!inputFile.eof()){
            inputFile >> nextKey;

            for(long i = 0; i < getCapacity(); i++)
            {
                int index = findIndex(nextKey, i);
                if(getValue(index) == -1)
                {
                    setValue(nextKey, index);
                    break;
                }
                else
                    numberOfCollisions++;
            }
        }

        inputFile.close();

        cout << "Number of collisions when insert operation: " << numberOfCollisions << endl;
    }
    else
        cout << fileName << " could not be opened!" << endl;

}

void search(string fileName)
{
    int numberOfCollisions = 0;

    ifstream inputFile(fileName.data());

    if(inputFile.is_open())
    {
        long nextKey;
        while(!inputFile.eof()){
            inputFile >> nextKey;

            for(long i = 0; i < getCapacity(); i++)
            {
                int index = findIndex(nextKey, i);
                if(getValue(index) != -1 && getValue(index) == nextKey)//No collision, slot is full with searched key
                    break;
                else if(getValue(index) != -1)//Collision, continue to search
                    numberOfCollisions++;
                else//Slot is empty
                    break;
            }
        }

        inputFile.close();

        cout << "Number of collisions when search operation: " << numberOfCollisions << endl;
    }
    else
        cout << fileName << " could not be opened!" << endl;
}
