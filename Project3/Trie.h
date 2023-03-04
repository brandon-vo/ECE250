#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include <iostream>
#include <vector>
using namespace std;

class Trie {
private:
    TrieNode *root;
    vector<TrieNode *> character;
    bool isEndOfWord;
    int countWords(TrieNode *node);

public:
    Trie();
    ~Trie();
    void insertWord(string word, bool load = false);
    void countWordsWithPrefix(string prefix);
    void remove (string& word);
};

#endif