////////////////////////////////////
// Brandon Vo - ECE 250 Project 2 //
////////////////////////////////////

#include "OpenAddressingTable.h"
#include "Process.h"
#include <iostream>
#include <vector>
using namespace std;

OpenAddressingTable::OpenAddressingTable(int n, int p) : HashTable(n, p) {}

void OpenAddressingTable::insertOpen(unsigned int pidKey) {

    // if the table is full, print failure and return
    if (this->currentSize == size) {
        cout << "failure" << endl;
        return;
    }

    // Get the primary and secondary hash values
    unsigned int h1 = getPrimaryHash(pidKey);
    unsigned int h2 = getSecondaryHash(pidKey);

    int i = 0;
    bool tombstoneFound = false;
    int tombstoneHash = 0;
    // Using double hashing if collision occurs
    while (!table[h1].empty() && i < size) {
        if (table[h1][0].getPID() == pidKey) {
            cout << "failure" << endl;
            return;
            // Mark that we found a tombstone. Used to continue checking if there is a duplicate pidKey in the table
        } else if (table[h1][0].getPID() == 0 && !tombstoneFound) {
            tombstoneFound = true;
            tombstoneHash = h1;
        }
        h1 = (h1 + h2) % size;
        i++;
    }

    // Replace tombstone with new process
    if (tombstoneFound) {
        table[tombstoneHash][0] = Process(pidKey, tombstoneHash, tombstoneHash);
        cout << "success" << endl;
        this->currentSize++;
        return;
    }

    // Insert new process into table
    table[h1].push_back(Process(pidKey, h1, h1));
    cout << "success" << endl;
    this->currentSize++;
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
        // Found the process to 'delete'
        if (table[h1][0].getPID() == pidKey) {
            table[h1][0].setPID(0); // Set PID to 0 to indicate tombstone
            this->currentSize--;    // Decrement current size
            cout << "success" << endl;
            return;
        }
        h1 = (h1 + h2) % size;
        i++;
    }
    cout << "failure" << endl;
}

void OpenAddressingTable::writeMemoryOpen(unsigned int pidKey, int addr, int x) {
    unsigned int h1 = getPrimaryHash(pidKey);
    unsigned int h2 = getSecondaryHash(pidKey);

    int i = 0;
    // Using double hashing if collision occurs
    while (!table[h1].empty() && table[h1][0].getPID() != pidKey && i < size) {
        h1 = (h1 + h2) % size;
        i++;
    }

    if (i == size || table[h1].empty()) {
        cout << "failure" << endl;
        return;
    }

    int memoryAddress = table[h1][0].getStartAddress() + addr;
    if (memoryAddress >= memorySize || addr >= pageSize) {
        cout << "failure" << endl;
        return;
    }

    memory[memoryAddress] = x;

    cout << "success" << endl;
}

void OpenAddressingTable::readMemoryOpen(unsigned int pidKey, int addr) {
    unsigned int h1 = getPrimaryHash(pidKey);
    unsigned int h2 = getSecondaryHash(pidKey);
    int i = 0;
    while (!table[h1].empty() && i < size) {
        if (table[h1][0].getPID() == pidKey) {
            int memoryAddress = table[h1][0].getStartAddress() + addr;
            if (memoryAddress >= 0 && memoryAddress < memorySize && addr < pageSize) {
                cout << addr << " " << memory[memoryAddress] << endl;
                return;
            } else {
                cout << "failure" << endl;
                return;
            }
        }
        h1 = (h1 + h2) % size;
        i++;
    }

    cout << "failure" << endl;
}