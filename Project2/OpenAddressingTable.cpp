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
    if (this->currentSize == size) {
        cout << "failure" << endl;
        return;
    }

    unsigned int h1 = getPrimaryHash(pidKey);
    unsigned int h2 = getSecondaryHash(pidKey);
    int pagesOccupied = 0;
    while (!table[h1].empty() && table[h1][0].getPID() != 0) {
        h1 = (h1 + h2) % size;
        pagesOccupied++;
    }

    int physicalAddress = h1 + (pagesOccupied * pageSize);
    table[h1].push_back(Process(pidKey, physicalAddress, h1));
    table[h1][0].setPID(pidKey);
    this->currentSize++;
    // cout << table[h1][0].getPID() << " " << table[h1][0].getStartAddress() << endl;
    cout << "success" << endl;

    // // print for debugging
    // for (int i = 0; i < size; i++) {
    //     if (!table[i].empty()) {
    //         for (unsigned int j = 0; j < table[i].size(); j++) {
    //             cout << table[i][j].getPID() << " " << table[i][j].getPhysicalAddress() << " -> ";
    //         }
    //     }
    // }
    // cout << endl;
}

void OpenAddressingTable::writeMemoryOpen(unsigned int pidKey, int addr, int x) {
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

    int memoryAddress = table[h1][0].getPhysicalAddress() + addr;
    if (memoryAddress >= memorySize || addr >= pageSize) { // && physicalAddr < pageSize) {        cout << "Address out of range." << endl;
        cout << "failure" << endl;
        return;
    }
    // cout << pidKey << " " << memoryAddress << " " << addr << " " << table[h1][0].getPhysicalAddress() << endl;
    memory[memoryAddress] = x;
    // cout << physicalAddr << " " << table[h1][0].getStartAddress() << " " << addr << endl;
    cout << "success" << endl;
}

void OpenAddressingTable::readMemoryOpen(unsigned int pidKey, int addr) {
    unsigned int h = getPrimaryHash(pidKey);
    unsigned int h2 = getSecondaryHash(pidKey);
    int i = 0;
    while (!table[h].empty() && i < size) {
        if (table[h][0].getPID() == pidKey) {
            int physicalAddr = table[h][0].getPhysicalAddress() + addr;
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
            table[h1][0].setPID(0);
            this->currentSize--;
            cout << "success" << endl;
            return;
        }
        h1 = (h1 + h2) % size;
        i++;
    }
    cout << "failure" << endl;
}