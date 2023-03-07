#include "Trie.h"
#include "illegal_exception.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    Trie myTrie;

    string command;
    string input;

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
                myTrie.countWordsWithPrefix(input);
            } catch (illegal_exception &e) {
                cout << e.what() << endl;
            }
        } else if (command == "e") {
            cin >> input;
            try {
                myTrie.removeWord(input);
            } catch (illegal_exception &e) {
                cout << e.what() << endl;
            }
        } else if (command == "p") {
            // myTrie.printWords(myTrie.getRoot(), "");
            myTrie.printTrie();
        } else if (command == "spellcheck") {
            cin >> input;
            myTrie.spellCheck(input);
        } else if (command == "empty") {
            myTrie.printIsEmpty();
        } else if (command == "clear") {
            myTrie.clear();
        } else if (command == "size") {
            myTrie.printWordCount();
        } else if (command == "exit") {
            break;
        }
    }
}