////////////////////////////////////
// Brandon Vo - ECE 250 Project 2 //
////////////////////////////////////

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Process.h"
#include <cmath>
#include <vector>
using namespace std;

class HashTable {
protected:
    int size;               // Size of table (m)
    int pageSize;           // Size of page (p)
    int currentSize;        // Current size of table
    int *memory;            // Memory array
    vector<Process> *table; // Vector of processes
public:
    HashTable(int n, int p);
    ~HashTable();
    int getPrimaryHash(int pidKey) const;
    int getSecondaryHash(int pidKey) const;
};

#endif