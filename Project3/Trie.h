#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include <iostream>
#include <vector>
using namespace std;

class Trie {
private:
    TrieNode *root;
    // vector<TrieNode *> character;
    int numberOfWords;
    // bool isEndOfWord;
    int countWords(TrieNode *node);
    void printWord(TrieNode *node, string word);
    void clearTrie(TrieNode *node);
public:
    Trie();
    ~Trie();
    void insertWord(string word, bool load = false);
    void countWordsWithPrefix(string prefix);
    void spellCheck(string word);
    void removeWord(string word);
    void printTrie();
    void printWordCount();
    void printIsEmpty();
    void clear();
    // TrieNode getRoot();
};

#endif