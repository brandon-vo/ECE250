#include "TrieNode.h"

#include <iostream>

TrieNode::TrieNode() {
    this->parent = nullptr;
    this->isEndOfWord = false;
    // this->numberOfWords = 0;
    this->childCount = 0;
    character = vector<pair<TrieNode *, int>>(26, make_pair(nullptr, 0));
    // character = vector<TrieNode *, int>[26];
    // for (int i = 0; i < 26; i++) {
    //     character[i] = nullptr;
    // }
}

TrieNode::~TrieNode() {
    for (int i = 0; i < character.size(); i++) {
        delete character[i].first;
    }
}

void TrieNode::getCharacter() {
    for (const auto& p : character) {
        if (p.first != nullptr) {
            // cout << (char)(p.first->character - 'A') << endl;
        }
    }
}