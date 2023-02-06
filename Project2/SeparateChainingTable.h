#ifndef ORDERED_TABLE_H
#define ORDERED_TABLE_H

#include "HashTable.h"
#include "Process.h"
#include <vector>
using namespace std;

class SeparateChainingTable  : public HashTable {
public:
    SeparateChainingTable(int n, int p);
    void insertOrdered(int pidKey);
    void searchOrdered(int pidKey);
    void writeMemoryOrdered(int pidKey, int addr, int x);
    void readMemoryOrdered(int pidKey, int addr);
    void printChain(int m);
    void deleteOrdered(int pidKey);
};

#endif