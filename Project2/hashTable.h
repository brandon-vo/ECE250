////////////////////////////////////
// Brandon Vo - ECE 250 Project 2 //
////////////////////////////////////

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
using namespace std;

class HashTable {
private:
    std::vector<int> table;
    int m; // Size of table
public:
    HashTable(int size);
    void insert(int key);
    bool search(int key);
    int primaryHash(int key);
    int secondaryHash(int key);
};

#endif