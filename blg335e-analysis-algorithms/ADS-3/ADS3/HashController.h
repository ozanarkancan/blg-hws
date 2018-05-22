#ifndef HASHCONTROLLER_H
#define HASHCONTROLLER_H

#include <string>
#include "HashTable.h"

using namespace std;

class HashController
{
    public:
        static void insert(HashTable& hTable, string fileName);
        static void search(HashTable& hTable, string fileName);
};

#endif // HASHCONTROLLER_H
