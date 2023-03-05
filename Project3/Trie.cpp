#include "Trie.h"
#include "illegal_exception.h"

#include <iostream>

using namespace std;

Trie::Trie() {
    root = new TrieNode();
    numberOfWords = 0;
}

Trie::~Trie() {
    delete root;
}

void Trie::insertWord(string word, bool load) {
    TrieNode *node = root;
    for (int i = 0; i < word.length(); i++) {
        if (!isupper(word[i])) {
            throw illegal_exception();
        }
        int index = word[i] - 'A';
        // if (index < 0 || index > 25) {
        //     throw illegal_exception();
        // }
        if (node->character[index] == nullptr) {
            node->character[index] = new TrieNode();
        }
        node = node->character[index];
    }
    if (node->isEndOfWord && !load) {
        // Word already exists in trie
        cout << "failure" << endl;
        return;
    } else if (!node->isEndOfWord) {
        // Word does not exist in trie, insert it
        node->isEndOfWord = true;
        numberOfWords++;
    }
    if (!load) {
        cout << "success" << endl;
        // cout << numberOfWords << endl;
    }
}

void Trie::countWordsWithPrefix(string prefix) {
    TrieNode *node = root;
    for (int i = 0; i < prefix.length(); i++) {
        if (!isupper(prefix[i])) {
            throw illegal_exception();
        }
        int index = prefix[i] - 'A';
        // if (index < 0 || index > 25) {
        //     throw illegal_exception();
        // }
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

// void Trie::removeWord(string word) {
//     TrieNode *current = root;
//     TrieNode *parent = nullptr;
//     int index;

//     // Traverse the trie based on the characters in the word
//     for (int i = 0; i < word.length(); i++) {
//         if (!isupper(word[i])) {
//             throw illegal_exception();
//         }
//         index = word[i] - 'A';
//         if (current->character[index] == nullptr) {
//             cout << "failure" << endl;
//             return;
//         }
//         parent = current;
//         current = current->character[index];
//     }

//     // If we reach here, we have found a node corresponding to the last character of the word
//     if (current->isEndOfWord) {
//         // The word is in the trie, erase it
//         current->isEndOfWord = false;
//         numberOfWords--;
//         cout << "success" << endl;

//         // Check if the node has children, if not, remove it from the trie
//         bool hasChildren = false;
//         for (int i = 0; i < 26; i++) {
//             if (current->character[i] != nullptr) {
//                 hasChildren = true;
//                 break;
//             }
//         }
//         if (!hasChildren) {
//             index = word[word.length()-1] - 'A';
//             parent->character[index] = nullptr;
//             delete current;
//         }
//     } else {
//         cout << "failure" << endl;
//     }
// }

void Trie::removeWord(string word) {
    TrieNode *current = root;

    // Traverse the trie based on the characters in the word
    for (int i = 0; i < word.length(); i++) {
        if (!isupper(word[i])) {
            throw illegal_exception();
        }
        int index = word[i] - 'A';
        if (current->character[index] == nullptr) {
            cout << "failure" << endl;
            return;
        }
        current = current->character[index];
    }

    // If we reach here, we have found a node corresponding to the last character of the word
    if (current->isEndOfWord) {
        // The word is in the trie, erase it
        current->isEndOfWord = false;
        numberOfWords--;
        cout << "success" << endl;
    }
}

void Trie::printWord(TrieNode *node, string word) {
    // cout << "countPrints is " << countPrints << " | numberOfWords: " << numberOfWords << endl;
    if (node->isEndOfWord) {
        cout << word << " ";
    }
    for (int i = 0; i < 26; i++) {
        if (node->character[i] != nullptr) {
            char ch = 'A' + i;
            string buildWord = word + ch;
            printWord(node->character[i], buildWord);
        }
    }
}

void Trie::printTrie() {
    if (numberOfWords == 0) {
        return;
    }
    printWord(root, "");
    cout << endl;
}

void Trie::printWordCount() {
    // int count = countWords(root);
    cout << "number of words is " << numberOfWords << endl;
    // cout << "number of words is " << count << endl;
}

void Trie::printIsEmpty() {
    // if (root == nullptr || countWords(root) == 0) {
    if (numberOfWords == 0) {
        cout << "empty 1" << endl;
    } else {
        cout << "empty 0" << endl;
    }
}

void Trie::spellCheck(string word) {
    TrieNode *current = root;
    string suggestion = "";

    // Traverse the trie based on the characters in the word
    for (int i = 0; i < word.length(); i++) {
        int index = word[i] - 'A';
        // cout << index << endl;
        // cout << current->character[index] << endl;
        // cout << word[i] << " " << current->character[index] << endl;
        if (current->character[index] == nullptr) {
            // No words in the trie start with the given letters
            // cout << "hello" << endl;
            // printWord(current, suggestion);
            // cout << endl;
            // return;
            // cout << "suggestion :" << suggestion << endl;
            break;
        }
        current = current->character[index];
        suggestion += word[i];
        // cout << current << " " << suggestion << endl;
    }

    // If we reach here, we have found a node corresponding to the last character of the word
    if (current->isEndOfWord) {
        // The word is in the trie
        cout << "correct" << endl;
    } else {
        // The word is not in the trie, suggest words
        // cout << "hi" <<  " " << suggestion << endl;
        printWord(current, suggestion);
        cout << endl;
    }
}

void Trie::clearTrie(TrieNode *node) {
    for (int i = 0; i < 26; i++) {
        if (node->character[i] != nullptr) {
            clearTrie(node->character[i]);
            delete node->character[i];
            node->character[i] = nullptr;
        }
    }
    node->isEndOfWord = false;
}

void Trie::clear() {
    clearTrie(root);
    root = new TrieNode();
    numberOfWords = 0;
    cout << "success" << endl;
}