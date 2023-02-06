#ifndef OPEN_TABLE_H
#define OPEN_TABLE_H

#include "HashTable.h"
#include "Process.h"
#include <vector>
using namespace std;

class OpenAddressingTable : public HashTable {
public:
    OpenAddressingTable(int n, int p);
    void insertDoubleHash(int pidKey);
    void searchOpen(int pidKey);
    void deleteOpen(int pidKey);
    void writeMemoryOpen(int pidKey, int addr, int x);
    void readMemoryOpen(int pidKey, int addr);
};

#endif