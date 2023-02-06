////////////////////////////////////
// Brandon Vo - ECE 250 Project 2 //
////////////////////////////////////

#include "SeparateChainingTable.h"
#include "Process.h"
#include <iostream>
#include <vector>
using namespace std;

SeparateChainingTable::SeparateChainingTable(int n, int p) : HashTable(n, p) {}

void SeparateChainingTable::insertOrdered(int pidKey) {
    // if table is full, print failure and return
    if (this->currentSize == size) {
        cout << "failure" << endl;
        return;
    }
    int h1 = getPrimaryHash(pidKey);
    // if pidKey is already in the table, print failure and return
    int i = 0;
    while (!table[h1].empty() && i < size) {
        if (table[h1][0].getPID() == pidKey) {
            cout << "failure" << endl;
            return;
        }
        h1 = h1 % size;
        i++;
    }
    // Find the correct position for the new process
    for (int j = 0; j < table[h1].size(); j++) {
        if (pidKey < table[h1][j].getPID()) {
            table[h1].insert(table[h1].begin() + j, Process(pidKey, h1));
            this->currentSize++;
            cout << "success" << endl;
            return;
        }
    }

    // If no position is found, insert at the end
    table[h1].push_back(Process(pidKey, h1));
    this->currentSize++;
    cout << "success" << endl;
}

void SeparateChainingTable::writeMemoryOrdered(int pidKey, int addr, int x) {
    int h1 = getPrimaryHash(pidKey);
    int i = 0;
    while (!table[h1].empty() && table[h1][0].getPID() != pidKey && i < size) {
        h1 = h1 % size;
        i++;
    }

    if (i == size) {
        cout << "failure" << endl;
        return;
    }

    memory[table[h1][0].getStartAddress() + addr] = x;
    cout << "success" << endl;
}

void SeparateChainingTable::readMemoryOrdered(int pidKey, int addr) {
    int h1 = getPrimaryHash(pidKey);
    int i = 0;
    while (!table[h1].empty() && i < size) {
        if (table[h1][0].getPID() == pidKey) {
            int physicalAddr = table[h1][0].getStartAddress() + addr;
            if (physicalAddr >= 0) { // && physicalAddr < pageSize) {
                int value = memory[physicalAddr];
                cout << addr << " " << value << endl;
                return;
            } else {
                cout << "failure" << endl;
                return;
            }
        }
        h1 = h1 % size;
        i++;
    }
    cout << "failure" << endl;
}

void SeparateChainingTable::printChain(int m) {
    if (table[m].empty()) {
        cout << "chain is empty" << endl;
    } else {
        for (int i = table[m].size() - 1; i >= 0; i--) {
            cout << table[m][i].getPID() << " ";
        }
        cout << endl;
    }
}

void SeparateChainingTable::searchOrdered(int pidKey) {
    int h1 = getPrimaryHash(pidKey);
    for (int i = 0; i < table[h1].size(); i++) {
        if (table[h1][i].getPID() == pidKey) {
            cout << "found " << pidKey << " in " << h1 << endl;
            return;
        }
    }
    cout << "not found" << endl;
}

void SeparateChainingTable::deleteOrdered(int pidKey) {
    int h1 = getPrimaryHash(pidKey);
    for (int i = 0; i < table[h1].size(); i++) {
        if (table[h1][i].getPID() == pidKey) {
            table[h1].erase(table[h1].begin() + i);
            this->currentSize--;
            cout << "success" << endl;
            return;
        }
    }
    cout << "failure" << endl;
}