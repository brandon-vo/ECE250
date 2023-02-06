////////////////////////////////////
// Brandon Vo - ECE 250 Project 2 //
////////////////////////////////////

#include "HashTable.h"
#include "Process.h"
#include <iostream>
#include <vector>
using namespace std;

HashTable::HashTable(int n, int p) {
    this->size = n / p;
    this->memorySize = n;
    this->pageSize = p;
    this->table = new vector<Process>[n / p];
    this->memory = new int[n];
}

HashTable::~HashTable() {
    for (int i = 0; i < memorySize / pageSize; i++) {
        table[i].clear();
    }
    delete[] table;
    delete[] memory;
}

unsigned int HashTable::getPrimaryHash(unsigned int pidKey) const {
    return pidKey % size; // h1
}

unsigned int HashTable::getSecondaryHash(unsigned int pidKey) const {
    unsigned int val = pidKey / size;
    // If even, add 1. If odd, return value.
    return ((val % size) % 2 == 0) ? val + 1 : val; // h2
}