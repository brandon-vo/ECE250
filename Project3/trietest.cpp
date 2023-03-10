////////////////////////////////////
// Brandon Vo - ECE 250 Project 3 //
////////////////////////////////////

#include "Trie.h"
#include "illegal_exception.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    Trie myTrie;    // Create a trie
    string command; // Command to be executed
    string input;   // Input parameter

    // Read in commands
    while (cin >> command) {
        if (command == "load") {
            ifstream fin("corpus.txt");
            while (fin >> input) {
                myTrie.insertWord(input, true);
            }
            fin.close();
            cout << "success" << endl;
        } else if (command == "i") {
            cin >> input;
            try {
                myTrie.insertWord(input);
            } catch (illegal_exception &e) {
                cout << e.what() << endl;
            }
        } else if (command == "c") {
            cin >> input;
            try {
                myTrie.countPrefix(input);
            } catch (illegal_exception &e) {
                cout << e.what() << endl;
            }
        } else if (command == "e") {
            cin >> input;
            try {
                myTrie.eraseWord(myTrie.getRoot(), input, input);
            } catch (illegal_exception &e) {
                cout << e.what() << endl;
            }
        } else if (command == "p") {
            if (myTrie.getNumberOfWords() == 0) {
                continue;
            } else {
                myTrie.printWord(myTrie.getRoot(), "");
                cout << endl;
            }
        } else if (command == "spellcheck") {
            cin >> input;
            myTrie.spellCheck(input);
        } else if (command == "empty") {
            cout << "empty " << (myTrie.getNumberOfWords() == 0) << endl;
        } else if (command == "clear") {
            myTrie.clearTrie();
            cout << "success" << endl;
        } else if (command == "size") {
            cout << "number of words is " << myTrie.getNumberOfWords() << endl;
        } else if (command == "exit") {
            break;
        }
    }
}