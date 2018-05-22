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

deque<string> getSonnets(ifstream& inputfile);
deque<string> getSentences(string sonnets);
deque<string> getWords(string&);
void cleanString(string&);
void printFile(ofstream&, node*);

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        tree bTree;
        bTree.setOrder(atoi(argv[1]));
        bTree.setMinimumDegree(atoi(argv[1]) / 2);
        ifstream input("sonnets.txt");
        short int article = 0;
        int x = 1;
        if(input.is_open())
        {
            deque<string> sonnetList;

            sonnetList = getSonnets(input);
            input.close();

            for(int k = 0; k < sonnetList.size(); k++)
            {
                deque<string> sentences;
                deque<string> words;
                sentences = getSentences(sonnetList[k]); // sonnets split into sentences

                for(short int i = 0; i < sentences.size(); i++)
                {
                    words = getWords(sentences[i]);
                    data d;
                    d.x = k + 1;
                    d.y = i + 1;

                    for(int j = 0; j < words.size(); j++)
                    {
                        if(!bTree.search(bTree.getRoot(), words[j], d))//Search if word is in tree or not
                        {
                            deque<data>* dataSet = new deque<data>;
                            dataSet->push_back(d);
                            bTree.insert(bTree.getRoot(), words[j], dataSet);
                        }
                    }
                }
            }

            cout << "B Tree is built" << endl;
            ofstream out("bTree.txt");
            if(!out.is_open())
                cout << "bTree could not written to file." << endl << endl;;
            printFile(out, bTree.getRoot());
            cout << "bTree is written to file." << endl;
            out.close();
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
            total = tFinish.tv_usec - tStart.tv_usec;

            for(int i = 0; i < 17; i++)
            {
                if(results[i] != NULL)
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is found in tree " << endl;
                    cout << "Datas: " << endl;
                    deque<data> ds = *(results[i]->dataSets[results[i]->getFound()]);
                    for(int j = 0; j < ds.size(); j++)
                        cout << "Sonnet: " << ds[j].x << " Sentence: " << ds[j].y << endl;
                }
                else
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is not found in tree " << endl;
                }
            }
            cout << endl <<"Running time for n = 17 : " << total <<  " microseconds" << endl;
            cout << "Press a key to continue" << endl;
            cin.get();

/*-------------------------------------n = 19----------------------------------------------------------*/


            total = 0;
            results.clear();
            gettimeofday(&tStart, NULL);
            for(int i = 0; i < 19; i++)
                results.push_back(bTree.search(bTree.getRoot(), searchKeys[i]));

            gettimeofday(&tFinish, NULL);
            total = tFinish.tv_usec - tStart.tv_usec;

            for(int i = 17; i < 19; i++)
            {
                if(results[i] != NULL)
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is found in tree " << endl;
                    cout << "Datas: " << endl;
                    deque<data> ds = *(results[i]->dataSets[results[i]->getFound()]);
                    for(int j = 0; j < ds.size(); j++)
                        cout << "Sonnet: " << ds[j].x << " Sentence: " << ds[j].y << endl;
                }
                else
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is not found in tree " << endl;
                }
            }
            cout << endl << "Running time for n = 19 : " << total <<  " microseconds" << endl;
            cout << "Press a key to continue" << endl;
            cin.get();

/*-------------------------------------n = 21----------------------------------------------------------*/

            total = 0;
            results.clear();
            gettimeofday(&tStart, NULL);
            for(int i = 0; i < 21; i++)
                results.push_back(bTree.search(bTree.getRoot(), searchKeys[i]));

            gettimeofday(&tFinish, NULL);
            total = tFinish.tv_usec - tStart.tv_usec;

            for(int i = 19; i < 21; i++)
            {
                if(results[i] != NULL)
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is found in tree " << endl;
                    cout << "Datas: " << endl;
                    deque<data> ds = *(results[i]->dataSets[results[i]->getFound()]);
                    for(int j = 0; j < ds.size(); j++)
                        cout << "Sonnet: " << ds[j].x << " Sentence: " << ds[j].y << endl;
                }
                else
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is not found in tree " << endl;
                }
            }
            cout << endl << "Running time for n = 21 : " << total <<  " microseconds" << endl;
            cout << "Press a key to continue" << endl;
            cin.get();

/*-------------------------------------n = 23----------------------------------------------------------*/

            total = 0;
            results.clear();
            gettimeofday(&tStart, NULL);
            for(int i = 0; i < 23; i++)
                results.push_back(bTree.search(bTree.getRoot(), searchKeys[i]));

            gettimeofday(&tFinish, NULL);
            total = tFinish.tv_usec - tStart.tv_usec;

            for(int i = 21; i < 23; i++)
            {
                if(results[i] != NULL)
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is found in tree " << endl;
                    cout << "Datas: " << endl;
                    deque<data> ds = *(results[i]->dataSets[results[i]->getFound()]);
                    for(int j = 0; j < ds.size(); j++)
                        cout << "Sonnet: " << ds[j].x << " Sentence: " << ds[j].y << endl;
                }
                else
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is not found in tree " << endl;
                }
            }
            cout << endl << "Running time for n = 23 : " << total <<  " microseconds" << endl;
            cout << "Press a key to continue" << endl;
            cin.get();

/*-------------------------------------n = 25----------------------------------------------------------*/

            total = 0;
            results.clear();
            gettimeofday(&tStart, NULL);
            for(int i = 0; i < 25; i++)
                results.push_back(bTree.search(bTree.getRoot(), searchKeys[i]));

            gettimeofday(&tFinish, NULL);
            total = tFinish.tv_usec - tStart.tv_usec;

            for(int i = 23; i < 25; i++)
            {
                if(results[i] != NULL)
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is found in tree " << endl;
                    cout << "Datas: " << endl;
                    deque<data> ds = *(results[i]->dataSets[results[i]->getFound()]);
                    for(int j = 0; j < ds.size(); j++)
                        cout << "Sonnet: " << ds[j].x << " Sentence: " << ds[j].y << endl;
                }
                else
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is not found in tree " << endl;
                }
            }
            cout << endl << "Running time for n = 25 : " << total <<  " microseconds" << endl;
            cout << "Press a key to continue" << endl;
            cin.get();

/*-------------------------------------n = 27----------------------------------------------------------*/

            total = 0;
            results.clear();
            gettimeofday(&tStart, NULL);
            for(int i = 0; i < 27; i++)
                results.push_back(bTree.search(bTree.getRoot(), searchKeys[i]));

            gettimeofday(&tFinish, NULL);
            total = tFinish.tv_usec - tStart.tv_usec;

            for(int i = 25; i < 27; i++)
            {
                if(results[i] != NULL)
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is found in tree " << endl;
                    cout << "Datas: " << endl;
                    deque<data> ds = *(results[i]->dataSets[results[i]->getFound()]);
                    for(int j = 0; j < ds.size(); j++)
                        cout << "Sonnet: " << ds[j].x << " Sentence: " << ds[j].y << endl;
                }
                else
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is not found in tree " << endl;
                }
            }
            cout << endl << "Running time for n = 27 : " << total <<  " microseconds" << endl;
            cout << "Press a key to continue" << endl;
            cin.get();

/*-------------------------------------n = 29----------------------------------------------------------*/

            total = 0;
            results.clear();
            gettimeofday(&tStart, NULL);
            for(int i = 0; i < 29; i++)
                results.push_back(bTree.search(bTree.getRoot(), searchKeys[i]));

            gettimeofday(&tFinish, NULL);
            total = tFinish.tv_usec - tStart.tv_usec;

            for(int i = 27; i < 29; i++)
            {
                if(results[i] != NULL)
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is found in tree " << endl;
                    cout << "Datas: " << endl;
                    deque<data> ds = *(results[i]->dataSets[results[i]->getFound()]);
                    for(int j = 0; j < ds.size(); j++)
                        cout << "Sonnet: " << ds[j].x << " Sentence: " << ds[j].y << endl;
                }
                else
                {
                    cout << endl << "'" << searchKeys[i] << "'" << " is not found in tree " << endl;
                }
            }
            cout << endl << "Running time for n = 29 : " << total <<  " microseconds" << endl;
            cout << "Press a key to continue" << endl;
            cin.get();
/*----------------------------------------------------------------------------------------------------------*/
        }//End if for file is opened
        else
            cout << "File could not open." << endl;

        return 0;
    }
    else
    {
        cout << "Please run program with m parameter" << endl;
    }
}

deque<string> getSonnets(ifstream& inputfile)
{
    deque<string> sonnetList;

    string line, sonnet("");
    while(!inputfile.eof())
    {
        getline (inputfile,line);
        if(line.size() == 0)
        {
            if(sonnet.size() != 0)
                sonnetList.push_back(sonnet);
            sonnet.clear();
        }
        else
            sonnet += line + "\n";
    }

    return sonnetList;
}

deque<string> getSentences(string sonnets)
{
    deque<string> sentenceList;
    int sentenceLength = 0;
    bool check = false;
    for(int i = 0; i < sonnets.size(); i++)
    {
        if(sonnets[i] == '!' || sonnets[i] == '?')
            check = true;
        else
        {
            if(sonnets[i] == '.')
            {
                if(!isalnum((int)sonnets[i+1]) && sonnets[i+1] != ',')
                {
                    if(sonnets[i-2] != '.')
                        check = true;
                }
            }
        }
        if(check)
        {
            if(sentenceLength != 0)
            {
                string str = sonnets.substr(i - sentenceLength, sentenceLength) + " "; //set a space for function getWords;
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

void printFile(ofstream& out, node* current)
{
    /*
    Writing node to file order
    Root
    Children (Left to Right)
    */

    out << "Number of keys: " << current->getNumberOfKeys() << endl;
    out << "Keys" << endl;

    for(int i = 0; i < current->keys.size(); i++)
    {
        out << current->keys[i] + " : ";
        for(int j = 0; j < (*(current->dataSets[i])).size(); j++)
        {
            out << "(" << (*(current->dataSets[i]))[j].x << ", " << (*(current->dataSets[i]))[j].y << ") ";
        }
        out << endl;
    }
    out << endl;

    if(current->children.size() != 0)
    {
        for(int i = 0; i < current->children.size(); i++)
        {
            printFile(out, current->children[i]);
        }
    }
}

