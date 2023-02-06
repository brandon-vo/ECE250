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
    this->pageSize = p;
    this->table = new vector<Process>[n / p];
    this->memory = new int[n];
}

HashTable::~HashTable() {
    // delete[] table;
    table->clear();
    table->shrink_to_fit();
    delete[] memory;
}

int HashTable::getPrimaryHash(int pidKey) const {
    return pidKey % size; // h1
}

int HashTable::getSecondaryHash(int pidKey) const {
    int val = pidKey / size;
    // If even, add 1. If odd, return value.
    return ((val % size) % 2 == 0) ? val + 1 : val; // h2
}