////////////////////////////////////
// Brandon Vo - ECE 250 Project 3 //
////////////////////////////////////

#include "TrieNode.h"

#include <iostream>

// Constructor
TrieNode::TrieNode() {
    for (int i = 0; i < 26; i++) {
        character[i] = nullptr;
    }
    this->parent = nullptr;
    this->isEndOfWord = false;
    this->counter = 0;
}

// Destructor
TrieNode::~TrieNode() {
    for (int i = 0; i < 26; i++) {
        if (character[i] != nullptr) {
            delete character[i];
        }
    }
}