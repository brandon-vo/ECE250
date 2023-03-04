#include "Trie.h"

#include <fstream>
#include <iostream>

using namespace std;

int main() {
    Trie myTrie;
    ifstream fin("corpus.txt");

    string command;
    string addWord;
    string prefix;
    while (cin >> command) {
        if (command == "load") {
            // read it all
            while (fin >> addWord) {
                myTrie.insertWord(addWord, true);
            }
            cout << "success" << endl;
        } else if (command == "i") {
            cin >> addWord;
            myTrie.insertWord(addWord);
        } else if (command == "c") {
            cin >> prefix;
            myTrie.countWordsWithPrefix(prefix);
        } else if (command == "p") {

        } else if (command == "spellcheck") {

        } else if (command == "empty") {

        } else if (command == "clear") {

        } else if (command == "size") {

        } else if (command == "exit") {
            break;
        }
    }
}