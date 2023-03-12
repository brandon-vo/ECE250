////////////////////////////////////
// Brandon Vo - ECE 250 Project 3 //
////////////////////////////////////

#include "Trie.h"
#include "illegal_exception.h"

// Constructor
Trie::Trie() {
    root = new TrieNode();
    numberOfWords = 0;
}

// Destructor
Trie::~Trie() {
    delete root;
}

// Insert a word into the trie
void Trie::insertWord(string word, bool load) {
    TrieNode *current = root;
    bool foundDuplicateWord = true;
    // Check if character is uppercase
    // Do this separately from the insertion loop so we prevent nodes before the illegal character from being created
    for (int i = 0; i < word.length(); i++) {
        if (!isupper(word[i])) {
            throw illegal_exception();
        }
        int index = word[i] - 'A'; // Get index of character from 0-25
        if (current->character[index] == nullptr) {
            foundDuplicateWord = false;  // If we found a null node, we know we haven't found a duplicate word
        } else if (foundDuplicateWord) { // If we found a duplicate word, we don't need to continue checking nodes
            current = current->character[index];
        }
    }
    // Duplicate word found. Don't insert word
    if (current->isEndOfWord && foundDuplicateWord) {
        if (!load) {
            cout << "failure" << endl;
        }
        return;
    }
    current = root;

    for (int i = 0; i < word.length(); i++) {

        int index = word[i] - 'A'; // Get index of character from 0-25

        // Create a new node if the path doesn't exist
        if (current->character[index] == nullptr) {
            current->character[index] = new TrieNode();  // Create new node
            current->character[index]->parent = current; // Set parent
        }
        current = current->character[index]; // Traverse
        current->counter++;                  // Increment counter
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
    // Don't print success if loading words from file
    if (!load) {
        cout << "success" << endl;
    }
}

// Erase a word from the trie
void Trie::eraseWord(TrieNode *node, string word, string deleteWord, bool nullFound) {
    // Check if start of word is uppercase
    if (!isupper(word[0])) {
        throw illegal_exception();
    }

    int index = word[0] - 'A'; // Get index of character from 0-25

    // Set flag and continue checking incase there is a non uppercase character later in the string
    // This is so we can throw the illegal exception if needed
    if (node->character[index] == nullptr) {
        nullFound = true;
    }

    word = word.substr(1); // Slice first character

    if (word.length() > 0) { // Continue traversing
        if (!nullFound) {    // Path exists
            node = node->character[index];
        }
        eraseWord(node, word, deleteWord, nullFound);
    } else {             // Reached end of word
        if (nullFound) { // Path doesn't exist
            cout << "failure" << endl;
            return;
        }
        if (node->character[index]->isEndOfWord) {       // Word exists in trie
            node->character[index]->isEndOfWord = false; // Mark node as not end of word
            numberOfWords--;                             // Decrement number of words counter in trie
            node->character[index]->counter--;           // Decrement counter
            // Check if node has any children, then delete node and traverse back up to parent
            if (!hasChildren(node->character[index])) {
                delete node->character[index]; // Remove the last node in the word
                node->character[index] = nullptr;
            }
            if (node != root) {
                node = node->parent;                   // Traverse back up to parent
                eraseRemainingNodes(node, deleteWord); // Recursive call to delete the rest of the nodes with no children
            }
            cout << "success" << endl;
            return;
        }
        // Word doesn't exist in trie
        cout << "failure" << endl;
    }
}

// Traverse back up the tree and delete nodes that are no longer needed
void Trie::eraseRemainingNodes(TrieNode *node, string deleteWord) {
    deleteWord.pop_back();                                 // Remove last character
    int index = deleteWord[deleteWord.length() - 1] - 'A'; // Get index of character from 0-25

    if (node->character[index] != nullptr) {
        node->character[index]->counter--; // Decrement counter
    }
    if (deleteWord.length() < 2) {
        return;
    }
    // Delete node then traverse back up to parent
    if (!hasChildren(node->character[index]) && node->character[index] != nullptr && !node->character[index]->isEndOfWord) {
        delete node->character[index];
        node->character[index] = nullptr;
    }
    node = node->parent;
    eraseRemainingNodes(node, deleteWord); // Recursive call
}

// Check if node has any children
bool Trie::hasChildren(TrieNode *node) {
    for (int i = 0; i < 26; i++) {
        if (node->character[i]) {
            return true;
        }
    }
    return false;
}

// Print all words in the trie
void Trie::printWord(TrieNode *node, string word) {
    if (node->isEndOfWord) { // Print word if it is the end of a word
        cout << word << " ";
    }
    // Recursively traverse the trie and build the word to print
    for (int i = 0; i < 26; i++) {
        if (node->character[i] != nullptr) {
            char ch = 'A' + i;
            string buildWord = word + ch;
            printWord(node->character[i], buildWord);
        }
    }
}

// Checks the inputted word or offers suggestions if the word is not spelled correctly
void Trie::spellCheck(string word) {
    TrieNode *current = root;
    string suggestion = ""; // Building the suggestion for the word

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
        current = current->character[index]; // Traverse
        suggestion += word[i];               // Build suggestion
    }

    if (current->isEndOfWord) { // Word is spelled correctly
        cout << "correct" << endl;
    } else {                            // Not spelled correctly
        printWord(current, suggestion); // Print suggestions
        cout << endl;
    }
}

// Clear the trie
void Trie::clearTrie() {
    for (int i = 0; i < 26; i++) {
        if (root->character[i] != nullptr) {
            delete root->character[i];
            root->character[i] = nullptr;
        }
    }
    this->numberOfWords = 0;
}

// Get the number of words that start with a given prefix
void Trie::getPrefixCount(string prefix) {

    TrieNode *current = root;

    for (int i = 0; i < prefix.length(); i++) {
        // Check if character is uppercase
        if (!isupper(prefix[i])) {
            throw illegal_exception();
        }
        int index = prefix[i] - 'A';                // Get index of character from 0-25
        if (current->character[index] == nullptr) { // Path doesn't exist
            cout << "not found" << endl;
            return;
        }
        current = current->character[index]; // Traverse
    }
    cout << "count is " << current->counter << endl; // Print number of words with prefix
}

// Get the number of words in the trie
int Trie::getNumberOfWords() {
    return numberOfWords;
}

// Get the root of the trie
TrieNode *Trie::getRoot() {
    return root;
}