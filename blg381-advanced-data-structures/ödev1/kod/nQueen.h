/*
* Course: BLG381E
* Homework #1
*
* Ozan Arkan CAN
* 040090573
*/

#ifndef NQUEEN_H
#define NQUEEN_H

class nQueen
{
    short int numberOfQueens;
    unsigned int numberOfSolutions;
    bool** board;
    short int* numbers;
    public:
        nQueen(short int);
        ~nQueen();
        void cleanboard();
        void permutation(short int*, short int, short int);
        void updateThreatenedPlaces(short int, short int);
        bool isProper(short int, short int);
        void swap(short int&, short int&);
        void showResult();
        short int* getList();
};

#endif // NQUEEN_H
