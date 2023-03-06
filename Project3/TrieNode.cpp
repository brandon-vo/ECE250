#include "TrieNode.h"

TrieNode::TrieNode() {
    this->isEndOfWord = false;
    // this->numberOfWords = 0;
    this->numberOfChildren = 0;
    character = vector<TrieNode *>(26);
}

TrieNode::~TrieNode() {
    for (int i = 0; i < 26; i++) {
        delete character[i];
    }
}

int TrieNode::getNumberOfChildren() {
    return numberOfChildren;
}

void TrieNode::incrementNumberOfChildren() {
    numberOfChildren++;
}

void TrieNode::decrementNumberOfChildren() {
    numberOfChildren--;
}

TrieNode *TrieNode::getChild(char c) {
    return character[c - 'A'];
}

void TrieNode::setChild(char c, TrieNode *node) {
    character[c - 'A'] = node;
    incrementNumberOfChildren();
}