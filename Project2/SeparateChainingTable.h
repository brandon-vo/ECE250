#ifndef ORDERED_TABLE_H
#define ORDERED_TABLE_H

#include "HashTable.h"
#include "Process.h"
#include <vector>
using namespace std;

class SeparateChainingTable : public HashTable {
private:
    vector<int> *availablePages; // vector of available pages: used as a FIFO queue

public:
    SeparateChainingTable(int n, int p);
    ~SeparateChainingTable();
    void insertOrdered(unsigned int pidKey);
    void searchOrdered(unsigned int pidKey);
    void deleteOrdered(unsigned int pidKey);
    void writeMemoryOrdered(unsigned int pidKey, int addr, int x);
    void readMemoryOrdered(unsigned int pidKey, int addr);
    void printChain(int m);
};

#endif