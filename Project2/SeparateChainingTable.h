#ifndef ORDERED_TABLE_H
#define ORDERED_TABLE_H

#include "HashTable.h"
#include "Process.h"
#include <vector>
using namespace std;

class SeparateChainingTable : public HashTable {
public:
    SeparateChainingTable(int n, int p);
    void insertOrdered(unsigned int pidKey);
    void searchOrdered(unsigned int pidKey);
    void writeMemoryOrdered(unsigned int pidKey, int addr, int x);
    void readMemoryOrdered(unsigned int pidKey, int addr);
    void printChain(int m);
    void deleteOrdered(unsigned int pidKey);
};

#endif