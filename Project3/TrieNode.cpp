#include "TrieNode.h"

TrieNode::TrieNode() {
    this->isEndOfWord = false;
    this->numberOfWords = 0;
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

bool TrieNode::hasMultipleChildren(TrieNode *node) {
    int numChildren = 0;
    for (TrieNode *child : node->character) {
        if (child != nullptr) {
            numChildren++;
        }
    }
    return numChildren > 1;
}

// bool TrieNode::hasMoreThanOneChild() {
//     int count = 0;
//     for (int i = 0; i < 26; i++) {
//         if (character[i] != nullptr) {
//             count++;
//         }
//     }
//     return count > 1;
// }

// void TrieNode::setNumberOfWords(int numberOfWords) {
//     this->numberOfWords = numberOfWords;
// }

// int TrieNode::getNumberOfWords() {
//     return this->numberOfWords;
// }

// void TrieNode::setIsEndOfWord(bool isEndOfWord) {
//     this->isEndOfWord = isEndOfWord;
// }

// bool TrieNode::getIsEndOfWord() {
//     return this->isEndOfWord;
// }