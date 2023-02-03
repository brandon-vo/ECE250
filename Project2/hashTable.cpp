////////////////////////////////////
// Brandon Vo - ECE 250 Project 2 //
////////////////////////////////////

#include "HashTable.h"
#include "Process.h"
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

HashTable::HashTable(int n, int p) {
    this->size = n / p;
    this->table = new vector<Process>[n / p];
    this->memory = new int[n];
}

int HashTable::getPrimaryHash(int pidKey) const {
    return pidKey % size; // h1
}

int HashTable::getSecondaryHash(int pidKey) const {
    int val = floor(pidKey / size);
    // If even, add 1. If odd, return value.
    return ((val % size) % 2 == 0) ? val + 1 : val; // h2
}

void HashTable::searchKey(int pidKey) {
    int h1 = getPrimaryHash(pidKey);
    for (int i = 0; i < table[h1].size(); i++) {
        if (table[h1][i].getPID() == pidKey) {
            cout << "found " << pidKey << " in " << h1 << endl;
            return;
        }
    }
    cout << "not found" << endl;
}