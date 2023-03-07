#include "Trie.h"
#include "illegal_exception.h"

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

        // cout << index << endl;
        if (current->character[index].first == nullptr) {
            // cout << "insert new node: " << word[i] << endl;
            current->character[index].first = new TrieNode();
        } else {
            // cout << "already exists: " << word[i] << endl;
            // current->character[index].second++;
        }
        current = current->character[index].first; // traverse
    }

    if (current->isEndOfWord && !load) {
        // Word already exists in trie
        cout << "failure" << endl;
        return;
    } else if (!current->isEndOfWord) {
        // Word does not exist in trie, insert it
        current->isEndOfWord = true;
        numberOfWords++;
    }
    if (!load) {
        cout << "success" << endl;
    }
}

// void Trie::insertWord(string word, bool load) {
//     TrieNode *current = root;
//     TrieNode *parent = nullptr;
//     for (int i = 0; i < word.length(); i++) {
//         if (!isupper(word[i])) {
//             throw illegal_exception();
//         }
//         int index = word[i] - 'A';
//         bool alreadyExists = false;
//         bool newChar = false;
//         parent = current;
//         // cout << "------------------" << endl;

//         if (current->character[index].first == nullptr) {
//             if (parent != nullptr) {
//                 // cout << "increase" << endl;
//                 // parent->childCount++;
//                 // if (i < word.length() - 1) {
//                 parent->character[index].second++;
//                 cout << "parent increase: " << parent->character[index].second << " parent: " << parent->character[index].first << endl;
//                 // }
//                 // parent->getCharacter();
//             }
//             current->character[index].first = new TrieNode();
//             cout << "new node for " << word[i] << " | ";
//             // current->getCharacter();
//             // newChar = true;
//         }
//         parent = current;
//         current = current->character[index].first;
//     }

// if (current->isEndOfWord && !load) {
//     // Word already exists in trie
//     cout << "failure" << endl;
//     return;
// } else if (!current->isEndOfWord) {
//     // Word does not exist in trie, insert it
//     current->isEndOfWord = true;
//     numberOfWords++;
// }
// if (!load) {
//     cout << "success" << endl;
// }
// }

void Trie::countWordsWithPrefix(string prefix) {
    TrieNode *node = root;
    for (int i = 0; i < prefix.length(); i++) {
        if (!isupper(prefix[i])) {
            throw illegal_exception();
        }
        int index = prefix[i] - 'A';
        if (node->character[index].first == nullptr) {
            cout << "not found" << endl;
            return;
        }
        node = node->character[index].first;
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
        if (node->character[i].first != nullptr) {
            count += countWords(node->character[i].first);
        }
    }
    return count;
}

void Trie::removeWord(string word) {
    TrieNode *current = root;
    bool notValid = false;
    // int maxChildCount = 0;
    // TrieNode *deleteNode = nullptr;
    // int indexToDelete = 0;
    // Traverse the trie based on the characters in the word
    for (int i = 0; i < word.length(); i++) {
        if (!isupper(word[i])) {
            throw illegal_exception();
        }
        // int currentChildCount = current->numberOfChildren;
        int index = word[i] - 'A';
        // cout << word[i] << " " << current->numberOfChildren << endl;
        // cout << current->character[index]->getNumberOfChildren() << endl;
        if (current->character[index].first == nullptr) {
            notValid = true; // Mark that the word is not in the trie.
            // Continue checking in case there is a non uppercase character later in the word
        } else {
            // current->numberOfChildren--;
            // cout << current->character[index].first << " -- " << current->character[index].second << endl;
            // if (current->character[index].second == 0) {
            //     // current->character[index].second = -1; // has been deleted
            //     deleteNode = current;
            //     indexToDelete = index;
            // }
            current = current->character[index].first;
        }
    }
    // cout << maxChildCount << endl;
    if (notValid || !current->isEndOfWord) {
        cout << "failure" << endl;
        return;
    }
    // If we reach here, we have found a node corresponding to the last character of the word
    // else if (current->isEndOfWord) {
    // The word is in the trie, erase it
    // deleteNode->character[indexToDelete].second = -1;
    current->isEndOfWord = false;
    numberOfWords--;
    cout << "success" << endl;
    // }
}

void Trie::printWord(TrieNode *node, string word) {
    // cout << "countPrints is " << countPrints << " | numberOfWords: " << numberOfWords << endl;
    if (node->isEndOfWord) {
        cout << word << " ";
        // cout << " -- " << endl;
    }
    for (int i = 0; i < 26; i++) {
        if (node->character[i].first != nullptr) {
            char ch = 'A' + i;
            string buildWord = word + ch;
            // cout << ch << " " << node->character[i].first << " " << node->character[i].second << " -> # of children" << endl;
            printWord(node->character[i].first, buildWord);
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
    // TrieNode *nodeWithError = nullptr;
    string suggestion = "";
    // string suggestionError = "";
    // bool foundDeleted = false;

    // Traverse the trie based on the characters in the word
    for (int i = 0; i < word.length(); i++) {
        int index = word[i] - 'A';
        // cout << current->character[index].first << " | " << current->character[index].second << " " << word[i] << " " << index << endl;
        // if (current->character[index].second > 0) {
        //     // cout << "found a split" << endl;
        //     nodeWithError = current->character[index].first;
        //     suggestionError = suggestion + word[i];
        //     // cout << suggestionError << endl;
        // }
        // if (current->character[index].second == -1) {
        //     foundDeleted = true;
        // }
        // cout << current->character[index].first << " " << word[i] << " " << index << endl;
        if (current->character[index].first == nullptr) {
            // No words in the trie start with the given letters
            if (suggestion.length() > 0) {
                printWord(current, suggestion);
            }
            cout << endl;
            return;
        }
        current = current->character[index].first;
        // cout << current << " " << word[i] << " " << index << endl;
        suggestion += word[i];
    }

    // If we reach here, we have found a node corresponding to the last character of the word
    if (current->isEndOfWord) {
        // The word is in the trie
        cout << "correct" << endl;
    } else {
        // TrieNode * test = root;
        // test = test->character[2];
        // test = test->character[0];
        // test = test->character[17];

        // todo: fix current to point to last node that branches of deleted node
        // todo: build suggestion string from root to new fixed current node

        // The word is not in the trie, suggest words
        // cout << " test " << endl;
        // if (nodeWithError != nullptr) {
        //     // cout << "ok" << " " << nodeWithError << " " << suggestionError << endl;
        //     printWord(nodeWithError, suggestionError);
        // } else {
        // if (foundDeleted) {
        //     printWord(nodeWithError, suggestionError);

        // } else {
        printWord(current, suggestion);
        // }

        cout << endl;
    }
}

void Trie::clearTrie(TrieNode *node) {
    for (int i = 0; i < 26; i++) {
        if (node->character[i].first != nullptr) {
            delete node->character[i].first;
            node->character[i].first = nullptr;
        }
    }
    node->isEndOfWord = false;
}

void Trie::clear() {
    clearTrie(root);
    numberOfWords = 0;
    cout << "success" << endl;
}