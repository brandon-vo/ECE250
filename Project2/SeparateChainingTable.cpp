// ////////////////////////////////////
// // Brandon Vo - ECE 250 Project 2 //
// ////////////////////////////////////

#include "SeparateChainingTable.h"
#include "Process.h"
#include <iostream>
#include <vector>
using namespace std;

SeparateChainingTable::SeparateChainingTable(int n, int p) : HashTable(n, p) {
    this->availablePages = new vector<int>;
    for (int i = 0; i < (n / p); i++) {
        this->availablePages->push_back(i);
    }
}

SeparateChainingTable::~SeparateChainingTable() {
    availablePages->clear();
    delete availablePages;
}

void SeparateChainingTable::insertOrdered(unsigned int pidKey) {
    if (availablePages->size() == 0) {
        cout << "failure" << endl;
        return;
    }
    unsigned int h1 = getPrimaryHash(pidKey);
    auto &bucket = table[h1];
    auto iterator = begin(bucket);
    while (iterator != end(bucket) && iterator->getPID() <= pidKey) {
        if (iterator->getPID() == pidKey) {
            cout << "failure" << endl; // pidKey already exists
            return;
        }
        iterator++;
    }
    if (h1 >= pageSize) { // lower value to calculate start address
        h1 = h1 - pageSize;
    }
    int startAddress = h1 + (availablePages->front() * pageSize);
    if (startAddress % 2 == 1) { // if odd
        startAddress--;          // make even
    }
    if (pageSize == 1) { // edge case
        startAddress = h1;
    }
    bucket.insert(iterator, Process(pidKey, startAddress, h1, availablePages->front()));
    availablePages->erase(availablePages->begin());
    this->currentSize++;
    cout << "success" << endl;
}

void SeparateChainingTable::deleteOrdered(unsigned int pidKey) {
    unsigned int h1 = getPrimaryHash(pidKey);
    auto &bucket = table[h1];
    auto iterator = begin(bucket);
    while (iterator != end(bucket)) {
        if (iterator->getPID() == pidKey) {
            iterator->setPID(0);
            iterator->setHash(-1);
            availablePages->push_back(iterator->getPage());
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
    if (bucket.size() == 0) {
        cout << "failure" << endl;
        return;
    }
    auto iterator = begin(bucket);
    while (iterator != end(bucket)) {
        if (iterator->getPID() == pidKey) {
            int memoryAddress = iterator->getStartAddress() + addr;
            if (memoryAddress < memorySize && addr >= 0 && addr < pageSize) {
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
            int memoryAddress = iterator->getStartAddress() + addr;
            if (memoryAddress < memorySize && addr >= 0 && addr < pageSize) {
                cout << addr << " " << memory[memoryAddress] << endl;
            } else {
                cout << "failure" << endl;
            }
            return;
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