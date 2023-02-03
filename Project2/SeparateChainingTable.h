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
    void deleteOrdered(int pidKey);
};

#endif