//
//  main.cpp
//  SimpleWordPredictor
//
//  Created by Aamir Jawaid on 2014-07-17.
//  Copyright (c) 2014 Aamir Jawaid. All rights reserved.
//

#include <iostream>
#include "Trie.h"

using namespace std;

int main(int argc, const char * argv[])
{
    Trie* myTrie = new Trie();
    cout << "Enter the filePath: " ;
    string input, options;
    getline(cin, input);
    if (myTrie->populate(input))
    {
        cout << "Trie was populated. Total notes created were " << myTrie->getTotalNodes() << "\n";
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

