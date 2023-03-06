#ifndef TRIENODE_H
#define TRIENODE_H

#include <vector>

using namespace std;

class TrieNode {
private:
    // int numberOfWords;
    // bool isEndOfWord;
    //     TrieNode* parent;
    // TrieNode *next;

public:
    vector<TrieNode *> character;
    // char character;
    // int numberOfWords;
    bool isEndOfWord;
    int numberOfChildren;
    TrieNode();
    ~TrieNode();
    int getNumberOfChildren();
    void incrementNumberOfChildren();
    void decrementNumberOfChildren();
    TrieNode *getChild(char c);
    void setChild(char c, TrieNode *node);
    // bool hasMultipleChildren(TrieNode *node);
    // bool hasMoreThanOneChild();
    //     void setNumberOfWords(int numberOfWords);
    //     int getNumberOfWords();
    //     void setIsEndOfWord(bool isEndOfWord);
    //     bool getIsEndOfWord();
};

#endif