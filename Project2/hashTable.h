////////////////////////////////////
// Brandon Vo - ECE 250 Project 2 //
////////////////////////////////////

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "Process.h"
#include <cmath>
#include <vector>
using namespace std;

class HashTable {
protected:
    int size;                     // Size of table (m)
    int memorySize;               // Size of memory (n)
    int pageSize;                 // Size of page (p)
    int currentSize;              // Current size of table
    int *memory;                  // Memory array
    vector<Process> *table;       // Vector of processes
public:
    HashTable(int n, int p);
    ~HashTable();
    unsigned int getPrimaryHash(unsigned int pidKey) const;
    unsigned int getSecondaryHash(unsigned int pidKey) const;
};

#endif