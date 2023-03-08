#include "TrieNode.h"

#include <iostream>

TrieNode::TrieNode() {
    this->isEndOfWord = false;
    this->parent = nullptr;
    for (int i = 0; i < 26; i++) {
        character[i] = nullptr;
    }
}

TrieNode::~TrieNode() {
    for (int i = 0; i < 26; i++) {
        delete character[i];
    }
}