////////////////////////////////////
// Brandon Vo - ECE 250 Project 2 //
////////////////////////////////////

#include "OpenAddressingTable.h"
#include "Process.h"
#include <iostream>
#include <vector>
using namespace std;

OpenAddressingTable::OpenAddressingTable(int n, int p) : HashTable(n, p) {}

void OpenAddressingTable::insertDoubleHash(unsigned int pidKey) {
    // todo: make sure that the pidKey is not already in the table and that the table is not full
    if (this->currentSize == size) {
        cout << "failure" << endl;
        return;
    }

    unsigned int h1 = getPrimaryHash(pidKey);
    unsigned int h2 = getSecondaryHash(pidKey);
    while (!table[h1].empty() && table[h1][0].getPID() != -1) {
        h1 = (h1 + h2) % size;
    }

    table[h1].push_back(Process(pidKey, h1));
    table[h1][0].setPID(pidKey);
    this->currentSize++;
    // cout << table[h1][0].getPID() << " " << table[h1][0].getStartAddress() << endl;
    cout << "success" << endl;
}

void OpenAddressingTable::writeMemoryOpen(unsigned int pidKey, int addr, int x) {
    // unsigned int h1 = getPrimaryHash(pidKey);
    // unsigned int h2 = getSecondaryHash(pidKey);
    // auto &bucket = table[h1];

    // for (auto &entry : bucket) {
    //     if (entry.getPID() == pidKey) {
    //         int physicalAddr = entry.getStartAddress() + addr;
    //         if (physicalAddr >= 0 && physicalAddr < memorySize && addr >= 0 && addr < pageSize) {
    //             memory[physicalAddr] = x;
    //             cout << "success" << endl;
    //             return;
    //         }
    //     } else {
    //         h1 = (h1 + h2) % size;
    //         bucket = table[h1];
    //     }
    // }

    // cout << "failure" << endl;

    // unsigned int h1 = getPrimaryHash(pidKey);
    // unsigned int h2 = getSecondaryHash(pidKey);
    // int i = 0;
    // while (!table[h1].empty() && i < size) {
    //     if (table[h1][0].getPID() == pidKey) {
    //         int physicalAddr = table[h1][0].getStartAddress() + addr;
    //         // cout << physicalAddr << " " << memorySize << " " << addr << " " << pageSize << endl;
    //         if (physicalAddr >= 0 && physicalAddr < memorySize && addr >= 0 && addr < pageSize) { // && physicalAddr < pageSize) {
    //             memory[physicalAddr] = x;
    //             cout << "success" << endl;
    //             return;
    //         } else {
    //             cout << "failure" << endl;
    //             return;
    //         }
    //     }
    //     h1 = (h1 + h2) % size;
    //     i++;
    // }
    // cout << "failure" << endl;
    // return;

    unsigned int h1 = getPrimaryHash(pidKey);
    unsigned int h2 = getSecondaryHash(pidKey);
    int i = 0;
    while (!table[h1].empty() && table[h1][0].getPID() != pidKey && i < size) {
        h1 = (h1 + h2) % size;
        i++;
    }

    if (i == size || table[h1].empty()) {
        cout << "failure" << endl;
        return;
    }

    int physicalAddr = table[h1][0].getStartAddress() + addr;
    if (physicalAddr >= memorySize || addr >= pageSize) { // && physicalAddr < pageSize) {        cout << "Address out of range." << endl;
        cout << "failure" << endl;
        return;
    }

    // write value x to memory at address addr
    memory[physicalAddr] = x;
    cout << "success" << endl;
}

void OpenAddressingTable::readMemoryOpen(unsigned int pidKey, int addr) {
    unsigned int h = getPrimaryHash(pidKey);
    unsigned int h2 = getSecondaryHash(pidKey);
    int i = 0;
    while (!table[h].empty() && i < size) {
        if (table[h][0].getPID() == pidKey) {
            int physicalAddr = table[h][0].getStartAddress() + addr;
            if (physicalAddr >= 0 && physicalAddr < memorySize && addr >= 0 && addr < pageSize) { // && physicalAddr < pageSize) {
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

void OpenAddressingTable::searchOpen(unsigned int pidKey) {
    unsigned int h1 = getPrimaryHash(pidKey);
    unsigned int h2 = getSecondaryHash(pidKey);
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

void OpenAddressingTable::deleteOpen(unsigned int pidKey) {
    unsigned int h1 = getPrimaryHash(pidKey);
    unsigned int h2 = getSecondaryHash(pidKey);
    int i = 0;
    while (!table[h1].empty() && i < size) {
        if (table[h1][0].getPID() == pidKey) {
            // TODO delete the process from the table
            table[h1][0].setPID(-1);
            this->currentSize--;
            cout << "success" << endl;
            return;
        }
        h1 = (h1 + h2) % size;
        i++;
    }
    cout << "failure" << endl;
}