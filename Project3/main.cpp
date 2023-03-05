#include "Trie.h"
#include "illegal_exception.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    Trie myTrie;
    ifstream fin("corpus.txt");

    string command;
    string word;
    string prefix;
    while (cin >> command) {
        if (command == "load") {
            while (fin >> word) {
                myTrie.insertWord(word, true);
            }
            cout << "success" << endl;
        } else if (command == "i") {
            cin >> word;
            try {
                myTrie.insertWord(word);
            } catch (illegal_exception &e) {
                cout << e.what() << endl;
            }
        } else if (command == "c") {
            cin >> prefix;
            try {
                myTrie.countWordsWithPrefix(prefix);
            } catch (illegal_exception &e) {
                cout << e.what() << endl;
            }
        } else if (command == "e") {
            cin >> word;
            try {
                myTrie.removeWord(word);
            } catch (illegal_exception &e) {
                cout << e.what() << endl;
            }
        } else if (command == "p") {
            // myTrie.printWords(myTrie.getRoot(), "");
            myTrie.printTrie();
        } else if (command == "spellcheck") {
            cin >> word;
            myTrie.spellCheck(word);
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