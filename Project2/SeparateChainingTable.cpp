////////////////////////////////////
// Brandon Vo - ECE 250 Project 2 //
////////////////////////////////////

#include "SeparateChainingTable.h"
#include "Process.h"
#include <iostream>
#include <vector>
using namespace std;

SeparateChainingTable::SeparateChainingTable(int n, int p) : HashTable(n, p) {}

void SeparateChainingTable::insertOrdered(int pidKey) {
    int h1 = getPrimaryHash(pidKey);
    // todo: make sure that the pidKey is not already in the table and that the table is not full
    table[h1].push_back(Process(pidKey, h1));
    cout << "success" << endl;

}