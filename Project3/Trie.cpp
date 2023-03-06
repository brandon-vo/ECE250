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
    TrieNode *current = root;
    for (int i = 0; i < word.length(); i++) {
        if (!isupper(word[i])) {
            throw illegal_exception();
        }
        int index = word[i] - 'A';
        if (current->character[index] == nullptr) {
            current->character[index] = new TrieNode();
            // cout << "new node" << endl;
        }
        current->numberOfChildren++;
        current = current->character[index];
        // current->character[index]->incrementNumberOfChildren(); // increment the number of children for the parent node
        // current->incrementNumberOfChildren(); // increment the number of children for the parent node
        // cout << word[i] << " " << index << " " << current->numberOfChildren << endl;
    }
    // cout << node -> numberOfChildren << endl;
    if (current->isEndOfWord && !load) {
        // Word already exists in trie
        cout << "failure" << endl;
        return;
    } else if (!current->isEndOfWord) {
        // Word does not exist in trie, insert it
        current->isEndOfWord = true;
        // current->incrementNumberOfChildren(); // increment the number of children for the parent node
        numberOfWords++;
    }
    if (!load) {
        cout << "success" << endl;
    }
}

void Trie::countWordsWithPrefix(string prefix) {
    TrieNode *node = root;
    for (int i = 0; i < prefix.length(); i++) {
        if (!isupper(prefix[i])) {
            throw illegal_exception();
        }
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

void Trie::removeWord(string word) {
    TrieNode *current = root;
    bool notValid = false;
    int maxChildCount = 0;
    // Traverse the trie based on the characters in the word
    for (int i = 0; i < word.length(); i++) {
        if (!isupper(word[i])) {
            throw illegal_exception();
        }
        int currentChildCount = current->numberOfChildren;
        int index = word[i] - 'A';
        // cout << word[i] << " " << current->numberOfChildren << endl;
        // cout << current->character[index]->getNumberOfChildren() << endl;
        if (current->character[index] == nullptr) {
            notValid = true; // Mark that the word is not in the trie.
            // Continue checking in case there is a non uppercase character later in the word
        } else {
            // current->numberOfChildren--;
            current = current->character[index];
        }
    }
    // cout << maxChildCount << endl;
    if (notValid) {
        cout << "failure" << endl;
        return;
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
        // cout << " -- " << endl;
    }
    for (int i = 0; i < 26; i++) {
        if (node->character[i] != nullptr) {
            char ch = 'A' + i;
            string buildWord = word + ch;
            // cout << ch << " " << node->character[i] << " " << node->numberOfChildren << " : # children" << endl;
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
        // cout << current->character[index] << " " << word[i] << endl;
        if (current->character[index] == nullptr) {
            // No words in the trie start with the given letters
            if (suggestion.length() > 0) {
                printWord(current, suggestion);
            }
            cout << endl;
            return;
        }
        current = current->character[index];
        suggestion += word[i];
    }

    // If we reach here, we have found a node corresponding to the last character of the word
    if (current->isEndOfWord) {
        // The word is in the trie
        cout << "correct" << endl;
    } else {
        // The word is not in the trie, suggest words
        printWord(current, suggestion);
        cout << endl;
    }
}

// void Trie::spellCheck(string word) {
//     TrieNode *current = root;
//     string suggestion = "";

//     // Traverse the trie based on the characters in the word
//     for (int i = 0; i < word.length(); i++) {
//         int index = word[i] - 'A';
//         // cout << index << endl;
//         // cout << current->character[index] << endl;
//         // cout << word[i] << " " << current->character[index] << endl;
//         if (current->character[index] == nullptr) {
//             // No words in the trie start with the given letters
//             // cout << "hello" << endl;
//             // printWord(current, suggestion);
//             // cout << endl;
//             // return;
//             // cout << "suggestion :" << suggestion << endl;
//             if (suggestion.length() > 0) {
//                 printWord(current, suggestion);
//             }
//             cout << endl;
//             return;
//         }
//         current = current->character[index];
//         suggestion += word[i];
//         // cout << current << " " << suggestion << endl;
//     }
//     // cout << word << " " << word.length() << " -- " << suggestion.length() << endl;
//     // if (word.length() < suggestion.length()) {
//     //     cout << "TEST suggestion :" << suggestion << endl;
//     // }
//     // If we reach here, we have found a node corresponding to the last character of the word
//     if (current->isEndOfWord) {
//         // The word is in the trie
//         cout << "correct" << endl;
//     } else {
//         // The word is not in the trie, suggest words
//         // cout << "hi" <<  " " << suggestion << endl;
//         // cout << "suggest" << " " << suggestion << endl;;
//         // if (suggestion != word) {
//             printWord(current, suggestion);
//         // }
//         cout << endl;
//     }
// }

void Trie::clearTrie(TrieNode *node) {
    for (int i = 0; i < 26; i++) {
        if (node->character[i] != nullptr) {
            delete node->character[i];
            node->character[i] = nullptr;
        }
    }
    node->isEndOfWord = false;
}

void Trie::clear() {
    clearTrie(root);
    numberOfWords = 0;
    cout << "success" << endl;
}