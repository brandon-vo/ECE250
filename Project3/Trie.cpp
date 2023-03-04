#include "Trie.h"

#include <iostream>

using namespace std;

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    delete root;
    // for (int i = 0; i < 26; i++) {
    //     delete character[i];
    // }
}

void Trie::insertWord(string word, bool load) {
    TrieNode *node = root;
    for (char ch : word) {
        int index = ch - 'A';
        if (node->character[index] == nullptr) {
            node->character[index] = new TrieNode();
        }
        node = node->character[index];
    }
    node->isEndOfWord = true;
    if (!load) {
        cout << "success" << endl;
    }
}

void Trie::countWordsWithPrefix(string prefix) {
    TrieNode *node = root;
    for (int i = 0; i < prefix.length(); i++) {
        int index = prefix[i] - 'A';
        if (node->character[index] == nullptr) {
            cout << "not found" << endl;
            return;
        }
        node = node->character[index];
    }

    int count = countWords(node);
    if (count > 0) {
        cout << "count is " << count << endl;
    } else {
        cout << "not found" << endl;
    }
}

int Trie::countWords(TrieNode *node) {
    int count = 0;
    if (node->isEndOfWord) {
        count++;
    }
    for (int i = 0; i < 26; i++) {
        if (node->character[i] != nullptr) {
            count += countWords(node->character[i]);
        }
    }
    return count;
}

// void Trie::remove(string& word) {
//     TrieNode* curr = root;
//     std::vector<TrieNode*> ancestors;
    
//     // Traverse the trie to find the node representing the last character of the word
//     for (char c : word) {
//         if (curr->character[c - 'A'] == nullptr) {
//             return; // Word is not in trie, do nothing
//         }
//         ancestors.push_back(curr);
//         curr = curr->character[c - 'A'];
//     }
    
//     // If the node representing the last character of the word is not a leaf, simply mark it as non-terminal
//     if (!curr->isEndOfWord) {
//         curr->isEndOfWord = false;
//         return;
//     }
    
//     // Otherwise, remove the node and its ancestors until reaching the first non-terminal node
//     curr->isEndOfWord = false;
//     while (!ancestors.empty()) {
//         curr = ancestors.back();
//         ancestors.pop_back();
//         char c = word[ancestors.size()];
//         TrieNode* child = curr->character[c - 'A'];
//         if (child == nullptr || child->isEndOfWord){// || hasChildren(child)) {
//             break;
//         }
//         curr->character[c - 'A'] = nullptr;
//         delete child;
//     }
// }