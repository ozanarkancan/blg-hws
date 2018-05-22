/**************************
*        BLG372E          *
* Analysis of Algorithm   *
*        Project 2        *
*                         *
*  Question 2             *
*                         *
*  Ozan Arkan CAN         *
*  040090573              *
*                         *
*                         *
**************************/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <string>
#include <math.h>
#include <deque>
#include <sys/time.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>

using namespace std;

deque<string> getWords(string&);
int getCost(int, int, deque<string>&);
int OptCost(int, deque<string>&, int);

int* functionValue;

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cout << "Wrong program call!" << endl;
        cout << "./question1 file_name maximum_char_per_line";
        return 1;
    }
    else
    {
        ifstream input(argv[1]);
        int maximumCharPerLine = atoi(argv[2]);
        int wordLength;
        int cost = 0;
		deque<string> words;
		string line;
        string word;
        timeval tStart, tFinish;
        double total = 0;

        if(!input.is_open())
        {
            cout << "Text file coud not opened!" << endl;
            return 1;
        }

		getline(input, line);
		input.close();
		words = getWords(line);

		functionValue = new int[words.size()];

        for(int i = 0; i < words.size(); i++)
            functionValue[i] = INT_MIN;

        cout << "Number of words in text : " << words.size() << endl;

        gettimeofday(&tStart, NULL);
        cost = OptCost(words.size() - 1, words, maximumCharPerLine);
        gettimeofday(&tFinish, NULL);

        total += ((tFinish.tv_sec - tStart.tv_sec)*1000 + (tFinish.tv_usec - tStart.tv_usec) / 1000.0);
        cout << "Cost: " << cost << endl;
        cout << "Running time: " << total << " milliseconds" << endl;

        delete[] functionValue;

        return 0;
    }
}

deque<string> getWords(string& text)
{
    deque<string> wordList;
    int wordLength = 0;
    int lastSpace;
    for(unsigned int i = 0; i < text.size(); i++)
    {
        if(isspace((int)text[i]))
        {
            if(wordLength != 0)
            {
                string str = text.substr(i - wordLength, wordLength);
                if(str.length() != 0)
                    wordList.push_back(str);
            }
            wordLength = 0;
            lastSpace = i;
        }
        else
            wordLength++;
    }

    wordList.push_back(text.substr(lastSpace + 1, text.size() - lastSpace + 1));
    return wordList;
}

int getCost(int i, int j, deque<string>& words, int maxCharPerLine)
{
    int cost;
	int difference;

	cost = 0;

    for(int count = i; count <= j; count++)
        cost += words[i].size();
    difference = maxCharPerLine - (cost + j - i);
    if(difference < 0)
        cost = INT_MAX;
    else
        cost = (int)pow((double)difference, 3);

    return cost;
}

int OptCost(int wordIndex, deque<string>& words, int maxCharPerLine)
{
    int cost = getCost(0, wordIndex, words, maxCharPerLine);
    int min = INT_MAX;
    int distance;

    if(cost == INT_MAX || cost == INT_MIN)
    {
        distance = wordIndex - (maxCharPerLine + 1) / 2; // calculate how many words in the line
        if(distance < 0)
            distance = 0;
        for(int i = distance; i < wordIndex; i++)
        {
            int currentValue;
            int tempCost = getCost(i + 1, wordIndex, words, maxCharPerLine);

            if(tempCost == INT_MAX)
                currentValue = INT_MAX;
            else
            {
                if(functionValue[i] == INT_MIN)//Calculate if value has not calculated yet
                    functionValue[i] = OptCost(i, words, maxCharPerLine);

                if(functionValue[i] == INT_MAX)
                    currentValue = INT_MAX;
                else
                    currentValue = tempCost + functionValue[i];
            }

			if(currentValue < min)//Hold minimum value
                min = currentValue;
        }

        return min;
    }
    else
        return cost;
}
