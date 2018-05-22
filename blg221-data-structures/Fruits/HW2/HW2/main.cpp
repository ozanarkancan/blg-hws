#include <iostream>
#include <fstream>
#include <string.h>
#include "Node.h"

using namespace std;

//Function signatures
int countWords();
void readFile(char*** words);
Node* createNewNode(char* word, int count);
Node* build_linked_list(char** array, int N);
Node* make_ordered_copy(Node* head);
void print_list(Node* head);
void deleteList(Node* head);

int main()
{
	int size = countWords();//To define dynamic array, get the size
	
	//Create array dynamically
	char** words = new char*[size];
	for(int i = 0; i < size; i++)
		words[i] = new char[LEN];
	
	readFile(&words);//Read file
	
	Node* firstList = build_linked_list(words, size);//Create list
	
	cout << "LINKED LIST1(UNORDERED)" << endl;
	print_list(firstList);//Print list
	
	Node* secondList = make_ordered_copy(firstList);//Create ordered list
	cout << endl << "LINKED LIST2(ORDERED)" << endl;
	print_list(secondList);//Print list
	
	//Delete lists to free memory area
	deleteList(firstList);
	deleteList(secondList);
	cout << endl << "To terminate pres a key..." << endl;
	cin.get();
	return 0;
}

int countWords()//Count the number of words in file
{
	fstream inputFile;
	inputFile.open("FRUITS.txt");//open file

	if(inputFile.is_open())
	{
		char word[LEN];
		int wordCount = 0;
		while ( inputFile.good() )//Read file line by line
		{
			//Get the data
			inputFile >> word;
			if(strcmp(word, "") != 0)
				wordCount++;
			else//There is invalid formatted text in file
				break;
		}
		inputFile.close();//Close the file
		return wordCount;
	}
	else//file could not opened
	{
		inputFile.close();//Close the file
		cout << "File could not be found" << endl;
		return 0;
	}
}

void readFile(char*** words)//Read file and assign words to given array
{
	fstream inputFile;
	inputFile.open("FRUITS.txt");//open file

	if(inputFile.is_open())
	{
		int wordCount = 0;
		while ( inputFile.good() )//Read file line by line
		{
			//Get the data
			inputFile >> (*words)[wordCount];
			if(strcmp((*words)[wordCount], "") != 0)
				wordCount++;
			else//There is invalid formatted text in file
				break;
		}
		inputFile.close();//Close the file
	}
	else//file could not opened
	{
		inputFile.close();//Close the file
		cout << "File could not be found" << endl;
	}
}

Node* createNewNode(char* word, int count)//Create new node
{
	Node* newNode = new Node();
	strcpy(newNode->word, word);//Copy the word
	newNode->count = count;//Set count
	newNode->next = NULL;//Initialize pointer

	return newNode;
}

Node* build_linked_list(char** array, int N)
{
	Node* head = NULL;//Initialize head
	for(int i = 0; i < N; i++)
	{
		Node* temp = head;
		while(temp)//Search list for current word
		{
			if(strcmp(temp->word, array[i]) == 0)//Word is in list
				break;
			else//Search next node
				temp = temp->next;
		}
		if(temp)//Word was found
			temp->count = temp->count + 1;//Increase count
		else//Word could not found
		{
			Node* newNode = createNewNode(array[i], 1);//Create new node
			//Insert new node to head
			newNode->next = head;
			head = newNode;
		}
	}

	return head;
}

Node* make_ordered_copy(Node* head)
{
	Node* newHead = NULL;
	Node* temp = head;
	while(temp)//Create copy of node in unordered list node by node
	{
		Node* copyNode = createNewNode(temp->word, temp->count);//Create copy

		if(!newHead)//There is no node insert to head
			newHead = copyNode;
		else
		{
			if(copyNode->count > newHead->count)//Insert to head
			{
				copyNode->next = newHead;
				newHead = copyNode;
			}
			else
			{
				Node* temp2 = newHead;
				Node* previous = temp2;
				while(temp2 && temp2->count >= copyNode->count)//Find proper place
				{
					previous = temp2;
					temp2 = temp2->next;
				}

				if(temp2)//There is a proper place
				{
					previous->next = copyNode;
					copyNode->next = temp2;
				}
				else//Insert to tail
					previous->next = copyNode;
				
			}
		}

		temp = temp->next;//Shift
	}
	return newHead;
}

void print_list(Node* head)
{
	Node* temp = head;
	while(temp)//Move node by node and print info
	{
		cout << temp->word << " : " << temp->count << endl;
		temp = temp->next;
	}
}

void deleteList(Node* head)//Free the memory area
{
	while(head)//Delete node by node
	{
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}
