#ifndef HASHTABLE_H
#define HASHTABLE_H


class HashTable
{
    public:
        HashTable(int m, int hashType);
        ~HashTable();
        int findIndex(long k, int i);
        void setValue(long value, int index);
        long getValue(int index);
        int getCapacity();
    private:
        int hashType;
        int hashSize;
        int* table;
        long* aj;
        int linearProbing(long k, int i);
        int doubleProbing(long k, int i);
        int universalHashing(long k, int i);
};

#endif // HASHTABLE_H
