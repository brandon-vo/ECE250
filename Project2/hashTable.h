////////////////////////////////////
// Brandon Vo - ECE 250 Project 2 //
////////////////////////////////////

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <cmath>
#include "Process.h"
using namespace std;

class HashTable {
protected:
    int size; // Size of table (m)
    vector<Process> *table; // Vector of processes
    int *memory; // Memory array
public:
    HashTable(int n, int p);
    int getPrimaryHash(int pidKey) const;
    int getSecondaryHash(int pidKey) const;
    void searchKey(int pidKey);
    void writeMemory(int pidKey, int addr, int x);
};

#endif