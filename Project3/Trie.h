////////////////////////////////////
// Brandon Vo - ECE 250 Project 3 //
////////////////////////////////////

#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include <iostream>
using namespace std;

class Trie {
private:
    TrieNode *root;
    int numberOfWords;
    bool hasChildren(TrieNode *node);
    void eraseRemainingNodes(TrieNode *node, string word);

public:
    Trie();
    ~Trie();
    void insertWord(string word, bool load = false);
    void eraseWord(TrieNode *node, string word, string deleteWord, bool nullFound = false);
    void printWord(TrieNode *node, string word);
    void spellCheck(string word);
    void clearTrie();
    void getPrefixCount(string prefix);
    int getNumberOfWords();
    TrieNode *getRoot();
};

#endif