#include "tree.h"

tree::tree()
{
    root = new node();
}

tree::~tree()
{
    cleenTree(root);
}

node* tree::getRoot(){ return root; }

void tree::setRoot(node* r){ root = r;}

int tree::getMinimumDegree(){ return t; }

void tree::setMinimumDegree(int val){ t = val; }

int tree::getOrder(){ return m; }

void tree::setOrder(int val){ m = val; }

void tree::split(node* x, int i, node* y)
{
    node *z = new node;
    z->setLeaf(y->getLeaf());
    z->setNumberOfKeys(getMinimumDegree() - 1);

    for(int j = 0; j < getMinimumDegree() - 1; j++)
        z->keys.push_back(y->keys[j + getMinimumDegree()]);

    y->keys.erase(y->keys.begin() + getMinimumDegree(), y->keys.end());

    for(int j = 0; j < getMinimumDegree() - 1; j++)
        z->dataSets.push_back(y->dataSets[j + getMinimumDegree()]);

    y->dataSets.erase(y->dataSets.begin() + getMinimumDegree(), y->dataSets.end());

    if(!y->getLeaf())
    {
        for(int j = 0; j < getMinimumDegree(); j++)
            z->children.push_back(y->children[j + getMinimumDegree()]);

        y->children.erase(y->children.begin() + getMinimumDegree(), y->children.end());
    }

    y->setNumberOfKeys(getMinimumDegree() - 1);

    for(int j = x->getNumberOfKeys(); j > i; j--)
    {
        if(j + 1 >= x->children.size())
            x->children.push_back(x->children[j]);
        else
            x->children[j+1] = x->children[j];
    }
    if(i + 1 >= x->children.size())
        x->children.push_back(z);
    else
        x->children[i+1] = z;

    for(int j = x->getNumberOfKeys() - 1; j >= i; j--)
    {
        if(j + 1 >= x->keys.size())
        {
            x->keys.push_back(x->keys[j]);
            x->dataSets.push_back(x->dataSets[j]);
        }
        else
        {
            x->keys[j+1] = x->keys[j];
            x->dataSets[j+1] = x->dataSets[j];
        }
    }

    if(i >= x->keys.size())
		x->keys.push_back(y->keys[getMinimumDegree() - 1]);
	else
		x->keys[i] = y->keys[getMinimumDegree() - 1];
    y->keys.pop_back();

    if(i >= x->dataSets.size())
		x->dataSets.push_back(y->dataSets[getMinimumDegree() - 1]);
	else
		x->dataSets[i] = y->dataSets[getMinimumDegree() - 1];
    y->dataSets.pop_back();

    x->setNumberOfKeys(x->getNumberOfKeys() + 1);
}

void tree::insert(node* T, string k, deque<data>* d)
{
    node* r = T;
    if(r->getNumberOfKeys() == getOrder() - 1)
    {
        node* s = new node();
        setRoot(s);
        s->setLeaf(false);
        s->setNumberOfKeys(0);
        s->children.push_back(r);
        split(s, 0, r);
        insertNonFull(s, k, d);
    }
    else
        insertNonFull(r, k, d);
}

void tree::insertNonFull(node* x, string k, deque<data>* d)
{
    int i = x->getNumberOfKeys();
    if(x->getLeaf())
    {
        while(i > 0 && k < x->keys[i - 1])
        {
            if(i >= x->keys.size())
            {
                x->keys.push_back(x->keys[i - 1]);
                x->dataSets.push_back(x->dataSets[i - 1]);
            }
            else
            {
                x->keys[i] = x->keys[i - 1];
                x->dataSets[i] = x->dataSets[i - 1];
            }
            i--;
        }
        if(i >= x->keys.size())
        {
            x->keys.push_back(k);
            x->dataSets.push_back(d);
        }
        else
        {
            x->keys[i] = k;
            x->dataSets[i] = d;
        }

        x->setNumberOfKeys(x->getNumberOfKeys() + 1);
    }
    else
    {
        while(i > 0 && k < x->keys[i - 1])
            i--;
        i++;
        if(x->children[i - 1]->getNumberOfKeys() == getOrder() - 1)
        {
            split(x, i - 1, x->children[i - 1]);
            if(k > x->keys[i - 1])
                i++;
        }
        insertNonFull(x->children[i - 1], k, d);
    }
}

node* tree::search(node* x, string k)
{
    int i = 0;
    while(i < x->getNumberOfKeys() && k > x->keys[i])
        i++;

    if(i < x->getNumberOfKeys() && k == x->keys[i])
    {
        x->setFound(i);
        return x;
    }

    if(x->getLeaf())
    {
        return NULL;
    }

    else
        return search(x->children[i], k);
}

bool tree::search(node* x, string k, data d)
{
    int i = 0;
    if(x->keys.size() != 0)
    {
        while(i < x->getNumberOfKeys() && k > x->keys[i])
            i++;
        if(i < x->getNumberOfKeys() && k == x->keys[i])
        {
            (x->dataSets[i])->push_back(d);
            return true;
        }
    }
    if(x->getLeaf())
        return false;
    else
        return search(x->children[i], k, d);
}

void tree::cleenTree(node* current)
{
    if(current->children.size() != 0)
    {
        for(int i = 0; i < current->children.size(); i++)
        {
            cleenTree(current->children[i]);
        }
    }

    delete current;
}
