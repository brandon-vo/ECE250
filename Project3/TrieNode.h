////////////////////////////////////
// Brandon Vo - ECE 250 Project 3 //
////////////////////////////////////

#ifndef TRIENODE_H
#define TRIENODE_H

#include <iostream>

class TrieNode {
public:
    TrieNode();
    ~TrieNode();
    TrieNode *character[26];
    TrieNode *parent;
    bool isEndOfWord;
};

#endif