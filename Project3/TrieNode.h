#ifndef TRIENODE_H
#define TRIENODE_H

#include <vector>

using namespace std;

class TrieNode {
    // private:
    //     TrieNode* parent;
    public:
        vector<TrieNode*> character;
        bool isEndOfWord;
        TrieNode();
        ~TrieNode();
};

#endif