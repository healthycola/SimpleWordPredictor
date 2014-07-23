//
//  Trie.cpp
//  WordPredictor
//
//  Created by Aamir Jawaid on 2014-07-22.
//  Copyright (c) 2014 Aamir Jawaid. All rights reserved.
//

#include "Trie.h"

void Trie::node::insert(string word, int charLocation, int *NodesExpanded)
{
    //cout << word << "\n";
    if (charLocation == word.length())
    {
        //last letter
        node* EndNode = new node('\0');
        children.push_back(EndNode);
        return;
    }
    else
    {
        vector<node*>::iterator child;
        for (child = children.begin(); child != children.end(); child++)
        {
            if ((*child)->val == word[charLocation])
                break;
        }
        
        if (child == children.end())
        {
            node* middleNode = new node(word[charLocation]);
            children.push_back(middleNode);
            (*NodesExpanded)++;
            return middleNode->insert(word, charLocation + 1, NodesExpanded);
        }
        else
        {
            return (*child)->insert(word, charLocation + 1, NodesExpanded);
        }
    }
}

string Trie::node::retrieve(string input, int charLocation)
{
    string output = "";
    if (charLocation <= input.length() - 1)
    {
        //Get to correct branch
        vector<node*>::iterator child;
        for (child = children.begin(); child != children.end(); child++)
        {
            if ((*child)->val == input[charLocation])
                break;
        }
        if (child == children.end())
            return "";
        else
        {
            return (*child)->retrieve(input, charLocation + 1);
        }
    }
    else if (val == '\0')
    {
        return input + "\n";
    }
    else if (charLocation == input.length())
    {
        for (vector<node*>::iterator child = children.begin(); child != children.end(); child++)
        {
            output += (*child)->retrieve(input, charLocation + 1);
        }
        return output;
    }
    else
    {
        //All the subsequent strings will be recommendations
        for (vector<node*>::iterator child = children.begin(); child != children.end(); child++)
        {
            output += (*child)->retrieve(input + val, charLocation + 1);
        }
        return output;
    }
}

void Trie::insert(string word)
{
    string wordToAdd = word;
    transform(wordToAdd.begin(), wordToAdd.end(), wordToAdd.begin(), ::tolower);
    portal->insert(wordToAdd, 0, &totalNodes);
}

string Trie::retrieve(string word)
{
    string wordToAdd = word;
    transform(wordToAdd.begin(), wordToAdd.end(), wordToAdd.begin(), ::tolower);
    return portal->retrieve(wordToAdd, 0);
}

bool Trie::populate(string fileName)
{
    string line;
    ifstream myfile (fileName);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            insert(line);
        }
        myfile.close();
        return true;
    }
    
    else cout << "Unable to open file" << "\n";
    return false;
}

