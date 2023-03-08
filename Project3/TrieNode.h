#ifndef TRIENODE_H
#define TRIENODE_H

#include <iostream>
using namespace std;

class TrieNode {
public:
    TrieNode();
    ~TrieNode();
    TrieNode *character[26];
    TrieNode *parent;
    bool isEndOfWord;
};

#endif