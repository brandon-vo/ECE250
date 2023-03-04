#include "TrieNode.h"

TrieNode::TrieNode() {
    this->isEndOfWord = false;
    character = vector<TrieNode *>(26, nullptr);
    // for (int i = 0; i < 26; i++) {
    //     this->children[i] = nullptr;
    // }
}

TrieNode::~TrieNode() {
    for (int i = 0; i < 26; i++) {
        delete character[i];
    }
}