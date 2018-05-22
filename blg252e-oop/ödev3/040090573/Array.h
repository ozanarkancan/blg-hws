/*
*
*	BLG 252E
*	2011 Spring
*	3rd Homework
*
*
*
*
*	Student Name: Ozan Arkan Can
*	Student ID  : 040090573
*
*
*/
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <string>

#define MAX 100 //Upperbound for array

using namespace std;

template <class type>
class Array
{
    int size;
    int inArray;
    type *head;
    public:
        Array(int);
        ~Array();
        int numberOfElement() {return inArray;}
		void decreaseNumberOfElement() {inArray--;}
		int getSize() {return size;}
        type operator[](int);
        void setElement(int, type);
        void print();
        type* find(const type&);
		type* popLast(){return &head[inArray-1];}

};

template <class type>
Array<type>::Array(int size)
{
    this->size = size;
    head = new type[size];
    inArray = 0;
}

template <class type>
Array<type>::~Array()
{
    delete[] head;
}

template <class type>
type Array<type>::operator[](int i)
{
    try{
        if(i <= 0 || i >= MAX) throw "Index exception!";
        return head[i];
    }
    catch(const char* s)
    {
        cout << s << endl;
    }

}


template <class type>
void Array<type>::setElement(int i, type T)
{
    try{
        if(i< 0 || i >= size) throw "Index exception!";
        head[i] = T;
        inArray++;
    }
    catch(const char* s)
    {
        cout << s << endl;
    }

}

template <class type>
void Array<type>::print()
{
    for(int i = 0; i < size; i++)
    {
        cout << head[i] << endl;
    }
}

template <class type>
type* Array<type>::find(const type& T)
{
    try
    {
        for(int i = 0; +i < size; i++)
        {
            if(head[i] == T)
                return &head[i];
        }
        throw "Element is not in array";
    }
    catch(const char* s)
    {
        cout << s << endl;
    }
}

#endif // ARRAY_H
