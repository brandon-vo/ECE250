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
    while (iterator != end(bucket) && pagesOccupied < pageSize) {
        if (iterator->getPID() == pidKey) {
            cout << "failure" << endl; // pidKey already exists
            return;
        }
        if (iterator->getStartAddress() / pageSize == h1) {
            pagesOccupied++;
        }
        if (iterator->getPID() > pidKey) {
            break;
        }
        iterator++;
    }
    // cout << "pagesOccupied: " << pagesOccupied << endl;
    table[h1].insert(iterator, Process(pidKey, h1 * pageSize + pagesOccupied * pageSize));
    this->currentSize++;
    cout << "success" << endl;

    // // print for debugging
    // for (int i = 0; i < size; i++) {
    //     if (!table[i].empty()) {
    //         for (unsigned int j = 0; j < table[i].size(); j++) {
    //             cout << table[i][j].getPID() << " " << table[i][j].getStartAddress() << "============" << endl;
    //         }
    //         cout << endl;
    //     }
    // }
}

void SeparateChainingTable::deleteOrdered(unsigned int pidKey) {
    unsigned int h1 = getPrimaryHash(pidKey);
    auto &bucket = table[h1];
    auto iterator = begin(bucket);
    while (iterator != end(bucket)) {
        if (iterator->getPID() == pidKey) {
            iterator->setPID(0);
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

    // int page = 1;
    // ISSUE: write 5 1 2, read 5 1 = 1 2. write 25 0 5, read 5 1 = 1 5. supposed to be 1 2
    while (iterator != end(bucket)) {
        if (iterator->getPID() == pidKey) {
            int physicalAddr = iterator->getStartAddress() + addr;
            // cout << physicalAddr << " " << memorySize << " " << iterator->getStartAddress() << " " << addr << endl;
            
            if (physicalAddr <= memorySize && addr >= 0 && addr < pageSize) {
                memory[physicalAddr-1] = x;
                cout << "success" << endl;
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

void SeparateChainingTable::readMemoryOrdered(unsigned int pidKey, int addr) {
    unsigned int h1 = getPrimaryHash(pidKey);
    auto &bucket = table[h1];
    auto iterator = begin(bucket);
    while (iterator != end(bucket)) {
        if (iterator->getPID() == pidKey) {
            int physicalAddr = iterator->getStartAddress() + addr;
            if (physicalAddr <= memorySize && addr >= 0 && addr < pageSize) {
                cout << addr << " " << memory[physicalAddr-1] << endl;
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

// void SeparateChainingTable::insertOrdered(unsigned int pidKey) {
//     // Check if the table is full
//     if (this->currentSize == size) {
//         cout << "failure" << endl;
//         return;
//     }

//     unsigned int h1 = getPrimaryHash(pidKey);
//     int i = 0;

//     // Check if the pidKey is already in the table
//     while (!table[h1].empty() && i < size) {
//         if (table[h1][0].getPID() == pidKey) {
//             cout << "failure" << endl;
//             return;
//         }
//         h1 = (h1) % size;
//         i++;
//     }

//     // Find the correct position for the new process
// for (int j = 0; j < table[h1].size(); j++) {
//     if (pidKey < table[h1][j].getPID()) {
//         table[h1].insert(table[h1].begin() + j, Process(pidKey, h1));
//         this->currentSize++;
//         cout << "success" << endl;
//         return;
//     }
// }

//     // If no position is found, insert at the end
// table[h1].push_back(Process(pidKey, h1));
// this->currentSize++;
// cout << "success" << endl;
// }

// void SeparateChainingTable::writeMemoryOrdered(unsigned int pidKey, int addr, int x) {

//     int h1 = getPrimaryHash(pidKey);
//     int i = 0;
//     while (!table[h1].empty() && table[h1][0].getPID() != pidKey && i < size) {
//         h1 = (h1 + 1) % size;
//         i++;
//     }

//     // if (i == size) {
//     //     cout << "failure" << endl;
//     //     return;
//     // }
// for (int i = 0; i < size; i++) {
//     if (!table[i].empty()) {
//         for (unsigned int j = 0; j < table[i].size(); j++) {
//             cout << "PID: " << table[i][j].getPID() << endl;
//             cout << "Start Address: " << table[i][j].getStartAddress() << endl;
//             // print other relevant information
//         }
//     }
// }
//     // cout << table[h1].empty() << endl;
//     cout << h1 << endl;
//     if (table[h1].empty() || table[h1][0].getPID() != pidKey) {
//         // cout << table[h1][0].getPID() << endl;
//         cout << "a" << endl;
//         cout << "failure" << endl;
//         return;
//     }
//     int physicalAddr = table[h1][0].getStartAddress() + addr;
//     if (physicalAddr >= memorySize || physicalAddr < 0 || addr < 0 || addr >= pageSize) {
//         cout << "b" << endl;
//         cout << "failure" << endl;
//         return;
//     }

//     memory[physicalAddr] = x;
//     cout << "success" << endl;

//     // unsigned int h1 = getPrimaryHash(pidKey);
//     // auto &bucket = table[h1];

//     // for (auto &entry : bucket) {
//     //     if (entry.getPID() == pidKey) {
//     //         int physicalAddr = entry.getStartAddress() + addr;
//     //         // cout << entry.getStartAddress() << " " << addr << " " << physicalAddr << " " << size << " " << memorySize << endl;
//     //         // ag_02: write 5 3 4 -> physical = 4, size = 16 / 4 = 4 SUCCESS (getting failure)
//     //         // ag_09: write 4 4 2 -> physical = 4, size = 4 / 1 = 4 FAILURE
//     //         if (physicalAddr >= 0 && physicalAddr < memorySize && addr >= 0 && addr < pageSize) {
//     //             cout << memory[physicalAddr] << endl;
//     //             memory[physicalAddr] = x;
//     //             cout << memory[physicalAddr] << endl;
//     //             cout << "success" << endl;
//     //             return;
//     //         }
//     //     }
//     //     h1 = h1 % size;
//     // }
//     // cout << "failure" << endl;
//     // return;

//     // int h1 = getPrimaryHash(pidKey);
//     // int i = 0;
//     // while (!table[h1].empty() && table[h1][0].getPID() != pidKey && i < size) {
//     //     h1 = (h1 + 1) % size;
//     //     i++;
//     // }
//     // // cout << i << endl;
//     // if (i == size){
//     //     cout << "failure" << endl;
//     //     return;
//     // }
//     // // if (!table[h1][0].getStartAddress()) {
//     // //     cout << "failure" << endl;
//     // //     return;
//     // // }
//     // // cout << addr << " " << table[h1][0].getStartAddress() << endl;
//     // // if (addr + table[h1][0].getStartAddress() == pageSize) { // fixes case 3 but weird
//     // //     cout << "failure" << endl;
//     // //     return;
//     // // }
//     // if (addr + table[h1][0].getStartAddress() > size) {
//     //     cout << "failure" << endl;
//     //     return;
//     // }

//     // memory[table[h1][0].getStartAddress() + addr] = x;
//     // cout << "success" << endl;
// }

// void SeparateChainingTable::readMemoryOrdered(unsigned int pidKey, int addr) {
//     unsigned int h1 = getPrimaryHash(pidKey);
//     auto &bucket = table[h1];

//     for (auto &entry : bucket) {
//         if (entry.getPID() == pidKey) {
//             int physicalAddr = entry.getStartAddress() + addr;
//             if (physicalAddr >= 0 && physicalAddr < memorySize && addr >= 0 && addr < pageSize) {
//                 int value = memory[physicalAddr];
//                 cout << addr << " " << value << endl;
//                 return;
//             }
//         }
//     }
//     cout << "failure" << endl;
//     return;

//     // unsigned int h1 = getPrimaryHash(pidKey);
//     // int i = 0;
//     // while (!table[h1].empty() && i < size) {
//     //     if (table[h1][0].getPID() == pidKey) {
//     //         int physicalAddr = table[h1][0].getStartAddress() + addr;
//     //         // cout << physicalAddr << endl;
//     //         if (physicalAddr >= 0 && physicalAddr < memorySize && addr >= 0) { // && physicalAddr < pageSize) {
//     //             int value = memory[physicalAddr];
//     //             cout << addr << " " << value << endl;
//     //             return;
//     //         } else {
//     //             cout << "failure" << endl;
//     //             return;
//     //         }
//     //     }
//     //     h1 = h1 % size;
//     //     i++;
//     // }
//     // cout << "failure" << endl;
// }

// void SeparateChainingTable::printChain(int m) {
// if (table[m].empty()) {
//     cout << "chain is empty" << endl;
// } else {
//     for (int i = table[m].size() - 1; i >= 0; i--) {
//         cout << table[m][i].getPID() << " ";
//     }
//     cout << endl;
// }
// }

// void SeparateChainingTable::searchOrdered(unsigned int pidKey) {
// unsigned int h1 = getPrimaryHash(pidKey);
// for (int i = 0; i < table[h1].size(); i++) {
//     if (table[h1][i].getPID() == pidKey) {
//         cout << "found " << pidKey << " in " << h1 << endl;
//         return;
//     }
// }
// cout << "not found" << endl;
// }

// void SeparateChainingTable::deleteOrdered(unsigned int pidKey) {
//     unsigned int h1 = getPrimaryHash(pidKey);
//     for (int i = 0; i < table[h1].size(); i++) {
//         if (table[h1][i].getPID() == pidKey) {
//             table[h1].erase(table[h1].begin() + i);
//             this->currentSize--;
//             cout << "success" << endl;
//             return;
//         }
//     }
//     cout << "failure" << endl;
// }