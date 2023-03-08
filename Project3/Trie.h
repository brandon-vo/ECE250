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

public:
    Trie();
    ~Trie();
    void insertWord(string word, bool load = false);
    void removeWord(TrieNode *node, string word, string wordCopy, bool nullFound = false, bool isDeleting = false);
    void countWords(string prefix);
    void printWord(TrieNode *node, string word);
    void spellCheck(string word);
    void clearTrie(TrieNode *node);
    void setNumberOfWords(int num);
    int getNumberOfWords();
    TrieNode *getRoot();
};

#endif