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
    TrieNode();
    ~TrieNode();
    vector<pair<TrieNode *, int>> character;
    // TrieNode* character[26];
    bool isEndOfWord;
    int childCount;
    TrieNode* parent;
    void getCharacter();
    // bool hasMultipleChildren(TrieNode *node);
    // bool hasMoreThanOneChild();
    //     void setNumberOfWords(int numberOfWords);
    //     int getNumberOfWords();
    //     void setIsEndOfWord(bool isEndOfWord);
    //     bool getIsEndOfWord();
};

#endif