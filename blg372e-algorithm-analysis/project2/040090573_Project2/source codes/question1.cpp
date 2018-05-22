/**************************
*        BLG372E          *
* Analysis of Algorithm   *
*        Project 2        *
*                         *
*  Question 1             *
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
#include <math.h>
#include <deque>
#include <sys/time.h>
#include <stdio.h>
#include <ctype.h>
#include <string>

using namespace std;

deque<string> getWords(string&);

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
        int lineLength = 0, wordLength;
        double cost = 0;
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

        cout << "Number of words in text : " << words.size() << endl;

        gettimeofday(&tStart, NULL);

        for(int i = 0; i < 1000; i++)
        {
            cost = 0;
            for(int i = 0; i < words.size(); i++)
            {
                word = words[i];
                wordLength = word.size();

                if(wordLength + lineLength <= maximumCharPerLine)
                    lineLength += wordLength + 1;
                else
                {
                    cost += pow((double)(maximumCharPerLine - (lineLength - 1)), 3);
                    lineLength = wordLength + 1;
                }
            }
        }

        gettimeofday(&tFinish, NULL);

        total += ((tFinish.tv_sec - tStart.tv_sec)*1000 + (tFinish.tv_usec - tStart.tv_usec) / 1000.0);
        total = total / 1000;
        cout << "Cost: " << cost << endl;
        cout << "Running time: " << total << " milliseconds" << endl;

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
