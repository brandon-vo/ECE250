#ifndef TRIENODE_H
#define TRIENODE_H

#include <vector>

using namespace std;

class TrieNode {
private:
    // int numberOfWords;
    // bool isEndOfWord;
    //     TrieNode* parent;
    TrieNode *next;

public:
    vector<TrieNode *> character;
    int numberOfWords;
    bool isEndOfWord;
    TrieNode();
    ~TrieNode();
    bool hasMultipleChildren(TrieNode *node);
    // bool hasMoreThanOneChild();
    //     void setNumberOfWords(int numberOfWords);
    //     int getNumberOfWords();
    //     void setIsEndOfWord(bool isEndOfWord);
    //     bool getIsEndOfWord();
};

#endif