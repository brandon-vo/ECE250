// ////////////////////////////////////
// // Brandon Vo - ECE 250 Project 2 //
// ////////////////////////////////////

#include "SeparateChainingTable.h"
#include "Process.h"
#include <iostream>
#include <vector>
using namespace std;

SeparateChainingTable::SeparateChainingTable(int n, int p) : HashTable(n, p) {}

void SeparateChainingTable::insertOrdered(unsigned int pidKey) {
    if (this->currentSize == size) {
        cout << "failure" << endl;
        return;
    }
    unsigned int h1 = getPrimaryHash(pidKey);
    auto &bucket = table[h1];
    auto iterator = begin(bucket);
    int pagesOccupied = 0;
    while (iterator != end(bucket)) {
        if (iterator->getPID() == pidKey) {
            cout << "failure" << endl; // pidKey already exists
            return;
        }
        // cout << iterator->getPID() << " ========== " << pidKey << endl;
        // if (iterator->getPhysicalAddress() / pageSize == h1 && pageSize != 1) {
        //     // cout << iterator->getPID() << " s " << endl;
        //     pagesOccupied++;
        // }
        // cout << "iterator->getHash(): " << iterator->getHash() << endl;
        if (iterator->getHash() == h1) {
            pagesOccupied++;
            // cout << "PAGE OCCUPIED: " << pagesOccupied << endl;
        }
        if (iterator->getPID() > pidKey) {
            // cout << "BREAK" << endl;
            break;
        }
        iterator++;
    }
    // cout << iterator->getHash() << " " << h1 << endl;
    // cout << "pagesOccupied: " << pagesOccupied << endl;
    int physicalAddress = h1 + (pageSize * pagesOccupied); // + (pagesOccupied * pageSize);// * pageSize + (pagesOccupied * pageSize);
    // storedAddresses->push_back(physicalAddress);
    // cout << pidKey << " " << physicalAddress << " " << pageSize << " " << pagesOccupied << endl;
    bucket.insert(iterator, Process(pidKey, physicalAddress, h1));
    // table[h1].insert(iterator, Process(pidKey, h1));

    this->currentSize++;
    cout << "success" << endl;
    // cout << bucket[0].getPID() << " XXXX " << bucket[0].getPhysicalAddress() << endl;
    // print for debugging
    // for (int i = 0; i < size; i++) {
    //     if (!table[i].empty()) {
    //         for (int j = 0; j < table[i].size(); j++) {
    //             cout << table[i][j].getPID() << " " << table[i][j].getPhysicalAddress() << " -> ";
    //         }
    //     }
    // }
    // cout << endl;
}

void SeparateChainingTable::deleteOrdered(unsigned int pidKey) {
    unsigned int h1 = getPrimaryHash(pidKey);
    auto &bucket = table[h1];
    auto iterator = begin(bucket);
    while (iterator != end(bucket)) {
        if (iterator->getPID() == pidKey) {
            iterator->setPID(0);
            iterator->setHash(-1);
            this->currentSize--;
            cout << "success" << endl;
            return;
        }
        iterator++;
    }
    cout << "failure" << endl;
}

void SeparateChainingTable::searchOrdered(unsigned int pidKey) {
    unsigned int h1 = getPrimaryHash(pidKey);
    auto &bucket = table[h1];
    for (int i = 0; i < bucket.size(); i++) {
        if (bucket[i].getPID() == pidKey) {
            cout << "found " << pidKey << " in " << h1 << endl;
            return;
        }
    }
    cout << "not found" << endl;
}

void SeparateChainingTable::writeMemoryOrdered(unsigned int pidKey, int addr, int x) {
    unsigned int h1 = getPrimaryHash(pidKey);
    auto &bucket = table[h1];
    auto iterator = begin(bucket);
    if (bucket.size() == 0) {
        cout << "failure" << endl;
        return;
    }

    while (iterator != end(bucket)) {
        if (iterator->getPID() == pidKey) {
            int memoryAddress = iterator->getPhysicalAddress() + addr;
            // cout << memoryAddress << " " << memorySize << " " << iterator->getPhysicalAddress() << " " << addr << endl;

            if (memoryAddress < memorySize && addr >= 0 && addr < pageSize) {
                // while (memory[memoryAddress] > 0) {
                //     // cout << "OVERRIDING" << endl;
                //     memoryAddress = memoryAddress + (pageSize * page);
                //     page++;
                // }
                memory[memoryAddress] = x;
                cout << "success" << endl;
                return;
            }
        }
        iterator++;
    }
    cout << "failure" << endl;
}

void SeparateChainingTable::readMemoryOrdered(unsigned int pidKey, int addr) {
    unsigned int h1 = getPrimaryHash(pidKey);
    auto &bucket = table[h1];
    auto iterator = begin(bucket);
    while (iterator != end(bucket)) {
        if (iterator->getPID() == pidKey) {
            int physicalAddr = iterator->getPhysicalAddress() + addr;
            if (physicalAddr < memorySize && addr >= 0 && addr < pageSize) {
                cout << addr << " " << memory[physicalAddr] << endl;
                return;
            } else {
                cout << "failure" << endl;
                return;
            }
        }
        iterator++;
    }
    cout << "failure" << endl;
}

void SeparateChainingTable::printChain(int m) {
    bool isEmpty = true; // Used for checking a chain full of 0's
    if (!table[m].empty()) {
        for (int i = table[m].size() - 1; i >= 0; i--) {
            if (table[m][i].getPID() != 0) {
                isEmpty = false;
                cout << table[m][i].getPID() << " ";
            }
        }
        if (!isEmpty) {
            cout << endl;
            return;
        }
    }
    cout << "chain is empty" << endl;
}