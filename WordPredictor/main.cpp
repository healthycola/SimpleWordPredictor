//
//  main.cpp
//  SimpleWordPredictor
//
//  Created by Aamir Jawaid on 2014-07-17.
//  Copyright (c) 2014 Aamir Jawaid. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

using namespace std;

template <typename T>
static void deletePtr(T* const ptr)
{
    delete ptr;
}

int totalNodes = 0;

class Trie {
private:
    struct node {
        char val;
        
        vector<node*> children;
        
        //insertion
        void insert(string word, int charLocation)
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
                    totalNodes++;
                    return middleNode->insert(word, charLocation + 1);
                }
                else
                {
                    return (*child)->insert(word, charLocation + 1);
                }
            }
        }
        
        string retrieve(string input, int charLocation)
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
        
        node()
        {}
        
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
    }
    
    ~Trie()
    {
        deletePtr<node>(portal);
    }
    //search
    
    void insert(string word)
    {
        string wordToAdd = word;
        transform(wordToAdd.begin(), wordToAdd.end(), wordToAdd.begin(), ::tolower);
        portal->insert(wordToAdd, 0);
    }
    
    string retrieve(string word)
    {
        string wordToAdd = word;
        transform(wordToAdd.begin(), wordToAdd.end(), wordToAdd.begin(), ::tolower);
        return portal->retrieve(wordToAdd, 0);
    }
    
    bool populate(string fileName)
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
};

int main(int argc, const char * argv[])
{
    
    // insert code here...
    Trie* myTrie = new Trie();
    cout << "Enter the filePath: " ;
    string input, options;
    getline(cin, input);
    if (myTrie->populate(input))
    {
        cout << "Trie was populated. Total notes created were " << totalNodes << "\n";
    }
    else
    {
        cout << "Sorry, Trie was not populated. \n";
        goto cleanup;
    }
    cout << "Enter a stream and we will tell you what words are possible. Enter quit to exit.\n";
    getline(cin, input);
    while (input != "quit")
    {
        options = myTrie->retrieve(input);
        cout << options;
        cout << "Next Word: ";
        getline(cin, input);
    }
cleanup:
    deletePtr<Trie>(myTrie);
    return 0;
}

