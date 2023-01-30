////////////////////////////////////
// Brandon Vo - ECE 250 Project 2 //
////////////////////////////////////

#include "hashTable.h"

#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int HashTable::primaryHash(int key) {
    return key % m; // h1
}

int HashTable::secondaryHash(int key) {
    int val = floor(key / m);
    // If even, add 1. If odd, return value.
    return ((val % m) % 2 == 0) ? val + 1 : val; // h2
}