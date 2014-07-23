//
//  Trie.h
//  WordPredictor
//
//  Created by Aamir Jawaid on 2014-07-22.
//  Copyright (c) 2014 Aamir Jawaid. All rights reserved.
//

#ifndef __WordPredictor__Trie__
#define __WordPredictor__Trie__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#endif /* defined(__WordPredictor__Trie__) */

using namespace std;
template <typename T>
static void deletePtr(T* const ptr)
{
    delete ptr;
}

class Trie {
private:
    int totalNodes = 0;
    struct node {
        char val;
        vector<node*> children;
        void insert(string word, int charLocation, int *NodesExpanded);
        string retrieve(string input, int charLocation);
        node() {}
        node(char input)
        {
            val = input;
        }
        ~node()
        {
            for_each(children.begin(), children.end(), deletePtr<node>);
        }
    };
    node* portal;
    
public:
    Trie()
    {
        portal = new node;
        totalNodes = 0;
    }
    
    ~Trie()
    {
        deletePtr<node>(portal);
    }
    
    int getTotalNodes()
    {
        return totalNodes;
    }
    
    void insert(string word);
    string retrieve(string word);
    bool populate(string fileName);
};
