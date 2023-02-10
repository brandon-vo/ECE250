////////////////////////////////////
// Brandon Vo - ECE 250 Project 2 //
////////////////////////////////////

#ifndef OPEN_ADDRESSING_TABLE_H
#define OPEN_ADDRESSING_TABLE_H

#include "HashTable.h"
#include "Process.h"
using namespace std;

class OpenAddressingTable : public HashTable {
public:
    OpenAddressingTable(int n, int p);
    void insertOpen(unsigned int pidKey);
    void searchOpen(unsigned int pidKey);
    void deleteOpen(unsigned int pidKey);
    void writeMemoryOpen(unsigned int pidKey, int addr, int x);
    void readMemoryOpen(unsigned int pidKey, int addr);
};

#endif