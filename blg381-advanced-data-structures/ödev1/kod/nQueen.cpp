/*
* Course: BLG381E
* Homework #1
*
* Ozan Arkan CAN
* 040090573
*/

#include "nQueen.h"
#include <iostream>

using namespace std;

nQueen::nQueen(short int numberOfQueens)
{
    this->numberOfQueens = numberOfQueens;
    numberOfSolutions = 0;
    board = new bool*[numberOfQueens];
    numbers = new short int[numberOfQueens];
    for(short int i = 0; i < numberOfQueens; i++)
    {
        board[i] = new bool[numberOfQueens];
        numbers[i] = i;
    }
    cleanboard();
}

nQueen::~nQueen()
{
    for(short int i = 0; i <  numberOfQueens; i++)
    {
        delete[] numbers;
        delete[] board[i];
    }
}

void nQueen::permutation(short int *numbers, short int k, short int m)
{
    if(k == m)
    {
        bool breakControl = false;
        for(short int i = 0; i <= m; i++)
        {
            if(isProper(numbers[i], i))
            {
                updateThreatenedPlaces(numbers[i], i);
            }
            else
            {
                breakControl = true;
                break;
            }
        }
        if(!breakControl)
        {
            numberOfSolutions++;
        }
        cleanboard();
    }
    else
    {
        for(short int i = k; i <= m; i++)
        {
            swap(numbers[k], numbers[i]);
            permutation(numbers, k+1, m);
            swap(numbers[k], numbers[i]);
        }
    }
}

void nQueen::swap(short int& x, short int& y)
{
    if(x != y)
    {
        x = x ^ y;
        y = x ^ y;
        x = x ^ y;
    }
}

void nQueen::cleanboard()
{
    for(short int i = 0; i < numberOfQueens; i++)
    {
        for(short int j = 0; j < numberOfQueens; j++)
        {
            board[i][j] = false;
        }
    }
}

void nQueen::showResult()
{
    cout << "Number of solutions: " << numberOfSolutions << endl;
}

bool nQueen::isProper(short int row, short int column)
{
    return !board[row][column];
}

void nQueen::updateThreatenedPlaces(short int row, short int column)
{
    for(short int i = 0; i < numberOfQueens; i++)
    {
        board[row][i] = true;
        board[i][column] = true;
    }

    //to left upper corner
    for(short int i = row - 1, j = column - 1; i >= 0 && j >= 0; i--, j--)
    {
        board[i][j] = true;
    }

    //to right bottom corner
    for(short int i = row + 1, j = column + 1; (i < numberOfQueens) && (j < numberOfQueens); i++, j++)
    {
        board[i][j] = true;
    }

    // to left bottom corner
    for(short int i = row + 1, j = column - 1; i < numberOfQueens && j >= 0; i++, j--)
    {
        board[i][j] = true;
    }

    //to right upper corner
    for(short int i = row - 1, j = column + 1; i >= 0 && j < numberOfQueens; i--, j++)
    {
        board[i][j] = true;
    }
}

short int* nQueen::getList()
{
    return numbers;
}
