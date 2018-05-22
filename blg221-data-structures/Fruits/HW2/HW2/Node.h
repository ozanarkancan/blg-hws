#ifndef NODE_H
#define NODE_H

#define LEN 20

struct Node
{
	char word[LEN];
	int count;
	Node* next;
};

#endif
