/*
* Course: BLG381E
* Homework #3
*
* Ozan Arkan CAN
* 040090573
*/

#include <iostream>
#include <fstream>
#include <deque>
#include <ctype.h>
#include "tree.h"
#include <sys/time.h>
#include <cstdlib>
#include <unistd.h>
#include <cstdio>

using namespace std;

string getArticle(ifstream& );
deque<string> getSentences(string&);
deque<string> getWords(string&);
void cleanString(string&);

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        tree bTree;
        bTree.setOrder(atoi(argv[1]));
        bTree.setMinimumDegree(atoi(argv[1]) / 2);
        ifstream input("reut2-000.sgm");
        short int article = 0;
        int x = 1;
        if(input.is_open())
        {
            string art;
            while(!input.eof())
            {
                deque<string> sentences;
                deque<string> words;
                art = getArticle(input);
                if(art == "")
                    break;
                sentences = getSentences(art);
                article++;
                for(short int i = 0; i < sentences.size(); i++)
                {
                    words = getWords(sentences[i]);
                    data d;
                    d.x = article;
                    d.y = i + 1;
                    for(int j = 0; j < words.size(); j++)
                    {
                        if(!bTree.search(bTree.getRoot(), words[j], d))
                        {
                            deque<data>* dataSet = new deque<data>;
                            dataSet->push_back(d);
                            bTree.insert(bTree.getRoot(), words[j], dataSet);
                        }
                    }
                }
            }
            input.close();
            cout << "B Tree is built" << endl << endl;
/*-----------------------------------------------------------------------------------------------------*/
/*------------------------------------Search Part------------------------------------------------------*/

            string searchKeys[29];
            timeval tStart, tFinish;
            double total = 0;
            deque<node*> results;
            cout  << "Program Searcher Part" << endl;
            cout << "Enter 29 string with a blank each two string" << endl;
            for(int i = 0; i < 29; i++)
                cin >> searchKeys[i];

/*-------------------------------------n = 17----------------------------------------------------------*/

            gettimeofday(&tStart, NULL);

            for(int i = 0; i < 17; i++)
                results.push_back(bTree.search(bTree.getRoot(), searchKeys[i]));

            gettimeofday(&tFinish, NULL);

            total += ((tFinish.tv_sec - tStart.tv_sec)*1000 + (tFinish.tv_usec - tStart.tv_usec) / 1000.0) + 0.5;
            for(int i = 0; i < 17; i++)
            {
                if(results[i] != NULL)
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is found in tree " << endl;
                    cout << "Datas: " << endl;
                    deque<data> ds = *(results[i]->dataSets[results[i]->getFound()]);
                    for(int j = 0; j < ds.size(); j++)
                        cout << "Article: " << ds[j].x << " Sentence: " << ds[j].y << endl;
                }
                else
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is not found in tree " << endl;
                }
            }
            cout << endl <<"Running time for n = 17 : " << total <<  " miliseconds" << endl;
            cout << "Press a key to continue" << endl;
            cin.get();

/*-------------------------------------n = 19----------------------------------------------------------*/


            total = 0;
            results.clear();
            gettimeofday(&tStart, NULL);

            for(int i = 0; i < 19; i++)
                results.push_back(bTree.search(bTree.getRoot(), searchKeys[i]));

            gettimeofday(&tFinish, NULL);

            total += ((tFinish.tv_sec - tStart.tv_sec)*1000 + (tFinish.tv_usec - tStart.tv_usec) / 1000.0) + 0.5;

            for(int i = 17; i < 19; i++)
            {
                if(results[i] != NULL)
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is found in tree " << endl;
                    cout << "Datas: " << endl;
                    deque<data> ds = *(results[i]->dataSets[results[i]->getFound()]);
                    for(int j = 0; j < ds.size(); j++)
                        cout << "Article: " << ds[j].x << " Sentence: " << ds[j].y << endl;
                }
                else
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is not found in tree " << endl;
                }
            }
            cout << endl << "Running time for n = 19 : " << total <<  " miliseconds" << endl;
            cout << "Press a key to continue" << endl;
            cin.get();

/*-------------------------------------n = 21----------------------------------------------------------*/

            total = 0;
            results.clear();
            gettimeofday(&tStart, NULL);

            for(int i = 0; i < 21; i++)
                results.push_back(bTree.search(bTree.getRoot(), searchKeys[i]));

            gettimeofday(&tFinish, NULL);

            total += ((tFinish.tv_sec - tStart.tv_sec)*1000 + (tFinish.tv_usec - tStart.tv_usec) / 1000.0) + 0.5;

            for(int i = 19; i < 21; i++)
            {
                if(results[i] != NULL)
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is found in tree " << endl;
                    cout << "Datas: " << endl;
                    deque<data> ds = *(results[i]->dataSets[results[i]->getFound()]);
                    for(int j = 0; j < ds.size(); j++)
                        cout << "Article: " << ds[j].x << " Sentence: " << ds[j].y << endl;
                }
                else
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is not found in tree " << endl;
                }
            }
            cout << endl << "Running time for n = 21 : " << total <<  " miliseconds" << endl;
            cout << "Press a key to continue" << endl;
            cin.get();

/*-------------------------------------n = 23----------------------------------------------------------*/

            total = 0;
            results.clear();
            gettimeofday(&tStart, NULL);

            for(int i = 0; i < 23; i++)
                results.push_back(bTree.search(bTree.getRoot(), searchKeys[i]));

            gettimeofday(&tFinish, NULL);

            total += ((tFinish.tv_sec - tStart.tv_sec)*1000 + (tFinish.tv_usec - tStart.tv_usec) / 1000.0) + 0.5;

            for(int i = 21; i < 23; i++)
            {
                if(results[i] != NULL)
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is found in tree " << endl;
                    cout << "Datas: " << endl;
                    deque<data> ds = *(results[i]->dataSets[results[i]->getFound()]);
                    for(int j = 0; j < ds.size(); j++)
                        cout << "Article: " << ds[j].x << " Sentence: " << ds[j].y << endl;
                }
                else
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is not found in tree " << endl;
                }
            }
            cout << endl << "Running time for n = 23 : " << total <<  " miliseconds" << endl;
            cout << "Press a key to continue" << endl;
            cin.get();

/*-------------------------------------n = 25----------------------------------------------------------*/

            total = 0;
            results.clear();
            gettimeofday(&tStart, NULL);

            for(int i = 0; i < 25; i++)
                results.push_back(bTree.search(bTree.getRoot(), searchKeys[i]));

            gettimeofday(&tFinish, NULL);

            total += ((tFinish.tv_sec - tStart.tv_sec)*1000 + (tFinish.tv_usec - tStart.tv_usec) / 1000.0) + 0.5;

            for(int i = 23; i < 25; i++)
            {
                if(results[i] != NULL)
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is found in tree " << endl;
                    cout << "Datas: " << endl;
                    deque<data> ds = *(results[i]->dataSets[results[i]->getFound()]);
                    for(int j = 0; j < ds.size(); j++)
                        cout << "Article: " << ds[j].x << " Sentence: " << ds[j].y << endl;
                }
                else
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is not found in tree " << endl;
                }
            }
            cout << endl << "Running time for n = 25 : " << total <<  " miliseconds" << endl;
            cout << "Press a key to continue" << endl;
            cin.get();

/*-------------------------------------n = 27----------------------------------------------------------*/

            total = 0;
            results.clear();
            gettimeofday(&tStart, NULL);

            for(int i = 0; i < 27; i++)
                results.push_back(bTree.search(bTree.getRoot(), searchKeys[i]));

            gettimeofday(&tFinish, NULL);

            total += ((tFinish.tv_sec - tStart.tv_sec)*1000 + (tFinish.tv_usec - tStart.tv_usec) / 1000.0) + 0.5;

            for(int i = 25; i < 27; i++)
            {
                if(results[i] != NULL)
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is found in tree " << endl;
                    cout << "Datas: " << endl;
                    deque<data> ds = *(results[i]->dataSets[results[i]->getFound()]);
                    for(int j = 0; j < ds.size(); j++)
                        cout << "Article: " << ds[j].x << " Sentence: " << ds[j].y << endl;
                }
                else
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is not found in tree " << endl;
                }
            }
            cout << endl << "Running time for n = 27 : " << total <<  " miliseconds" << endl;
            cout << "Press a key to continue" << endl;
            cin.get();

/*-------------------------------------n = 29----------------------------------------------------------*/

            total = 0;
            results.clear();
            gettimeofday(&tStart, NULL);

            for(int i = 0; i < 29; i++)
                results.push_back(bTree.search(bTree.getRoot(), searchKeys[i]));

            gettimeofday(&tFinish, NULL);

            total += ((tFinish.tv_sec - tStart.tv_sec)*1000 + (tFinish.tv_usec - tStart.tv_usec) / 1000.0) + 0.5;

            for(int i = 27; i < 29; i++)
            {
                if(results[i] != NULL)
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is found in tree " << endl;
                    cout << "Datas: " << endl;
                    deque<data> ds = *(results[i]->dataSets[results[i]->getFound()]);
                    for(int j = 0; j < ds.size(); j++)
                        cout << "Article: " << ds[j].x << " Sentence: " << ds[j].y << endl;
                }
                else
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is not found in tree " << endl;
                }
            }
            cout << endl << "Running time for n = 29 : " << total <<  " miliseconds" << endl;
            cout << "Press a key to continue" << endl;
            cin.get();
/*----------------------------------------------------------------------------------------------------------*/
        }//End if for file is opened
        else
            cout << "File could not open." << endl;

        return 0;
    }
}

string getArticle(ifstream& inputfile)
{
    string line, article("");
        bool check = false;
        int index, index2;
        while(!inputfile.eof())
        {
            getline (inputfile,line);
            index = line.find("<BODY>");
            index2 = line.find("</BODY");
            if(check)
            {
                if(index2 != string::npos)
                {
                    check = false;
                    article.erase(article.size() - 1);
                    return article;
                }
                else
                    article += line + "\n";
            }
            else
            {
                if(index  != string::npos)
                {
                    check = true;
                    article += line.substr(index+6);
                    article += "\n";
                }
            }
        }
}

deque<string> getSentences(string& article)
{
    deque<string> sentenceList;
    int sentenceLength = 0;
    bool check = false;
    for(int i = 0; i < article.size() - 6; i++)
    {
        if(article[i] == '!' || article[i] == '?')
            check = true;
        else
        {
            if(article[i] == '.')
            {
                if(!isalnum((int)article[i+1]) && article[i+1] != ',')
                {
                    if(article[i-2] != '.')
                        check = true;
                }
            }
            else
            {
                if(article[i] == ' ' && article[i + 1] == ' ' && article[i + 2] == ' ' && article[i + 3] == ' ')
                    check = true;
            }
        }
        if(check)
        {
            if(sentenceLength != 0)
            {
                string str = article.substr(i - sentenceLength, sentenceLength) + " "; //set a space for function getWords;
                if(str.size() != 0)
                    sentenceList.push_back(str);

            }
            sentenceLength = 0;
            check = false;
            i++;
        }
        else
            sentenceLength++;
    }
    sentenceList.push_back(article.substr(article.size() - 6, 6) + " "); //Add reuter
    return sentenceList;
}

deque<string> getWords(string& sentence)
{
    deque<string> wordList;
    int wordLength = 0;
    for(int i = 0; i < sentence.size(); i++)
    {
        if(isspace((int)sentence[i]))
        {
            if(wordLength != 0)
            {
                string str = sentence.substr(i - wordLength, wordLength);
                cleanString(str);
                if(str.length() != 0)
                    wordList.push_back(str);
            }
            wordLength = 0;

        }
        else
            wordLength++;
    }
    return wordList;
}

void cleanString(string& word)
{
    for(int i = 0; i < word.length(); i++)
    {
        if(!isalpha((int)word[i]))
        {
            string::iterator it = word.begin() + i;
            i--;
            word.erase(it);
        }
        else
           word[i] =  tolower((int)word[i]);
    }
}
