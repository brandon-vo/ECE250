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
    // todo: make sure that the pidKey is not already in the table and that the table is not full
    if (!table->empty()) {
        cout << "failure" << endl;
        return;
    }
    int h1 = getPrimaryHash(pidKey);
    int h2 = getSecondaryHash(pidKey);
    while (!table[h1].empty()) {
        h1 = (h1 + h2) % size;
    }

    table[h1].push_back(Process(pidKey, h1));
    cout << table[h1][0].getPID() << " " << table[h1][0].getStartAddress() << endl;
    cout << "success" << endl;
}