#include "heap.h"
#include <iostream>

using namespace std;

Heap::Heap(unsigned capacity)
{
    this->capacity = capacity;
    this->heapSize = 0;
    this->heap = new double[capacity];
}

Heap::~Heap()
{
    if(this->heap != NULL)
        delete[] this->heap;
}

void Heap::MAX_HEAPIFY(int i)
{
    int l = 2 * i + 1;
    int r = 2 * (i + 1);
    int largest;

    if(l <= this->heapSize && this->heap[l] > this->heap[i])
        largest = l;
    else
        largest = i;
    if(r <= this->heapSize && this->heap[r] > this->heap[largest])
        largest = r;
    if(largest != i)
    {
        swap(this->heap[i], this->heap[largest]);
        MAX_HEAPIFY(largest);
    }
}

void Heap::HEAP_INCREASE_KEY(int i, double key)
{
    if(i >= this->heapSize)//Check heap size
        throw "Index out of boundary.";

    if(key < this->heap[i])
        throw "New key smaller than current key.";

    this->heap[i] = key;

    int parent = (i - 1) / 2;
    while(i > 0 && this->heap[parent] < this->heap[i])//Move until parent greater than all child
    {
        swap(this->heap[i], this->heap[parent]);
        i = parent;
        parent = (i - 1) / 2;
    }
}

void Heap::MAX_HEAP_INSERT(double key)
{
    if(this->heapSize == this->capacity)//Check heap capacity
        throw "Heap overflow.";

    this->heapSize++;
    this->heap[this->heapSize - 1] = -1;//Add a node to end of heap
    HEAP_INCREASE_KEY(this->heapSize - 1, key);//Update value of that node
}

double Heap::HEAP_EXTRACT_MAX()
{
    if(this->heapSize == 0)
        throw "Heap underflow.";

    double max = this->heap[0];//Extract top of heap
    this->heap[0] = this->heap[this->heapSize - 1];//Move last node to root
    this->heapSize--;
    MAX_HEAPIFY(0);

    return max;
}

void Heap::swap(double& x, double& y)
{
    double tmp = x;
    x = y;
    y = tmp;
}

int Heap::getHeapSize()
{
    return this->heapSize;
}

double Heap::getKey(int i)
{
    if(i >= this->heapSize)
        throw "Index out of boundary";
    return this->heap[i];
}
