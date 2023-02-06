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
    if (this->currentSize == size) {
        cout << "failure" << endl;
        return;
    }
    // if (table->size() == size) {
    //     cout << "failure" << endl;
    //     return;
    // }
    int h1 = getPrimaryHash(pidKey);
    int h2 = getSecondaryHash(pidKey);
    while (!table[h1].empty()) {
        h1 = (h1 + h2) % size;
    }

    table[h1].push_back(Process(pidKey, h1));
    this->currentSize++;
    // cout << table[h1][0].getPID() << " " << table[h1][0].getStartAddress() << endl;
    cout << "success" << endl;
}

void OpenAddressingTable::writeMemoryOpen(int pidKey, int addr, int x) {
    int h1 = getPrimaryHash(pidKey);
    int h2 = getSecondaryHash(pidKey);
    int i = 0;
    while (!table[h1].empty() && table[h1][0].getPID() != pidKey && i < size) {
        h1 = (h1 + h2) % size;
        i++;
    }

    if (i == size) {
        cout << "failure" << endl;
        return;
    }

    // if (table[h1][0].getStartAddress() + addr >= table[h1][0].getStartAddress() + table[h1][0].get() || addr < 0) {
    //     cout << "Address out of range." << endl;
    //     return;
    // }

    // write value x to memory at address addr
    memory[table[h1][0].getStartAddress() + addr] = x;
    cout << "success" << endl;
}

void OpenAddressingTable::readMemoryOpen(int pidKey, int addr) {
    int h = getPrimaryHash(pidKey);
    int h2 = getSecondaryHash(pidKey);
    int i = 0;
    while (!table[h].empty() && i < size) {
        if (table[h][0].getPID() == pidKey) {
            int physicalAddr = table[h][0].getStartAddress() + addr;
            if (physicalAddr >= 0) { // && physicalAddr < pageSize) {
                int value = memory[physicalAddr];
                cout << addr << " " << value << endl;
                return;
            } else {
                cout << "failure" << endl;
                return;
            }
        }
        h = (h + h2) % size;
        i++;
    }
    cout << "failure" << endl;
}

void OpenAddressingTable::searchOpen(int pidKey) {
    int h1 = getPrimaryHash(pidKey);
    int h2 = getSecondaryHash(pidKey);
    int i = 0;
    while (!table[h1].empty() && i < size) {
        if (table[h1][0].getPID() == pidKey) {
            cout << "found " << pidKey << " in " << h1 << endl;
            return;
        }
        h1 = (h1 + h2) % size;
        i++;
    }
    cout << "not found" << endl;
}

void OpenAddressingTable::deleteOpen(int pidKey) {
    int h1 = getPrimaryHash(pidKey);
    int h2 = getSecondaryHash(pidKey);
    int i = 0;
    while (!table[h1].empty() && i < size) {
        if (table[h1][0].getPID() == pidKey) {
            table[h1].clear();
            // cout << table[h1][0].getPID() << endl;
            this->currentSize--;
            cout << "success" << endl;
            return;
        }
        h1 = (h1 + h2) % size;
        i++;
    }
    cout << "failure" << endl;
}