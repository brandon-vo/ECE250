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
    void deleteOpen(int pidKey);
};

#endif