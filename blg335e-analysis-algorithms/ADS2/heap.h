#ifndef HEAP_H
#define HEAP_H


class Heap
{
    public:
        Heap(unsigned capacity);
        ~Heap();

        void MAX_HEAP_INSERT(double key);
        double HEAP_EXTRACT_MAX();
        int getHeapSize();
        double getKey(int i);
        void HEAP_INCREASE_KEY(int i, double key);

    private:
        //Members
        int capacity;
        int heapSize;
        double* heap;

        //Methods
        void MAX_HEAPIFY(int i);
        void swap(double&, double&);
};

#endif // HEAP_H
