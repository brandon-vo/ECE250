////////////////////////////////////
// Brandon Vo - ECE 250 Project 2 //
////////////////////////////////////

#include "OpenAddressingTable.h"
#include "Process.h"
#include <iostream>
#include <vector>
using namespace std;

OpenAddressingTable::OpenAddressingTable(int n, int p) : HashTable(n, p) {}

void OpenAddressingTable::insertDoubleHash(int pidKey) {
    int h1 = getPrimaryHash(pidKey);
    int h2 = getSecondaryHash(pidKey);
    // todo: make sure that the pidKey is not already in the table and that the table is not full
    for (int i = 0; i < size; i++) {
        int index = (h1 + i * h2) % size;
        if (table[index].empty()) {
            table[index].push_back(Process(pidKey, index));
            cout << "success" << endl;
            return;
        }
    }
}