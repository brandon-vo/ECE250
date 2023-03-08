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

        if (current->character[index] == nullptr) {
            current->character[index] = new TrieNode();
            current->character[index]->parent = current;
        }
        current = current->character[index]; // traverse
    }

    if (current->isEndOfWord && !load) {
        // Word already exists in trie
        cout << "failure" << endl;
        return;
    } else if (!current->isEndOfWord) {
        // Mark the last node as the end of a word (leaf)
        current->isEndOfWord = true;
        numberOfWords++;
    }
    if (!load) {
        cout << "success" << endl;
    }
}

void Trie::countWords(string prefix) {
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

    int count = countWordsUtil(node);
    if (count > 0) {
        cout << "count is " << count << endl;
    } else {
        cout << "not found" << endl;
    }
}

int Trie::countWordsUtil(TrieNode *node) {
    int count = 0;
    if (node->isEndOfWord) {
        count++;
    }
    for (int i = 0; i < 26; i++) {
        if (node->character[i] != nullptr) {
            count += countWordsUtil(node->character[i]);
        }
    }
    return count;
}

void Trie::removeWord(TrieNode *node, string word, string deleteWord, bool nullFound, bool isDeleting) {
    // traversing back up the tree
    if (isDeleting) {
        if (deleteWord.length() == 1) {
            return;
        }
        deleteWord.pop_back();

        int index = deleteWord[deleteWord.length() - 1] - 'A';

        // delete node then traverse back up
        if (!hasChildren(node->character[index]) && !node->character[index]->isEndOfWord) {
            delete node->character[index];
            node->character[index] = nullptr;
            node = node->parent;
            removeWord(node, word, deleteWord, nullFound, true);
        }
    } else {
        if (!isupper(word[0])) {
            throw illegal_exception();
        }

        int index = word[0] - 'A';

        if (node->character[index] == nullptr) {
            nullFound = true;
            // set flag and continue checking incase there is a non uppercase character later in the string
        }

        word = word.substr(1); // cut off first character

        if (word.length() > 0) {
            if (!nullFound) {
                node = node->character[index];
            }
            removeWord(node, word, deleteWord, nullFound);
        } else {
            if (nullFound) {
                cout << "failure" << endl;
                return;
            }
            if (node->character[index]->isEndOfWord) {
                node->character[index]->isEndOfWord = false;

                if (!hasChildren(node->character[index])) {
                    // delete node then traverse back up
                    delete node->character[index];
                    node->character[index] = nullptr;
                    node = node->parent;
                    removeWord(node, word, deleteWord, nullFound, true);
                }
                numberOfWords--;
                cout << "success" << endl;
                return;
            }
            cout << "failure" << endl;
        }
    }
}

bool Trie::hasChildren(TrieNode *node) {
    for (int i = 0; i < 26; i++) {
        if (node->character[i]) {
            return true;
        }
    }
    return false;
}

void Trie::printWord(TrieNode *node, string word) {
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

void Trie::spellCheck(string word) {
    TrieNode *current = root;
    string suggestion = "";

    // Traverse the trie based on the characters in the word
    for (int i = 0; i < word.length(); i++) {
        int index = word[i] - 'A';
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

    if (current->isEndOfWord) {
        cout << "correct" << endl;
    } else {
        printWord(current, suggestion);
        cout << endl;
    }
}

void Trie::clearTrie(TrieNode *node) {
    for (int i = 0; i < 26; i++) {
        if (node->character[i] != nullptr) {
            delete node->character[i];
            node->character[i] = nullptr;
        }
    }
}

void Trie::setNumberOfWords(int num) {
    numberOfWords = num;
}

int Trie::getNumberOfWords() {
    return numberOfWords;
}

TrieNode *Trie::getRoot() {
    return root;
}