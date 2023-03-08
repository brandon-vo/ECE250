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
    int countWordsUtil(TrieNode *node);
    void eraseRemainingNodes(TrieNode *node, string word);

public:
    Trie();
    ~Trie();
    void insertWord(string word, bool load = false);
    void eraseWord(TrieNode *node, string word, string wordCopy, bool nullFound = false);
    void countWords(string prefix);
    void printWord(TrieNode *node, string word);
    void spellCheck(string word);
    void clearTrie(TrieNode *node);
    int getNumberOfWords();
    TrieNode *getRoot();
};

#endif