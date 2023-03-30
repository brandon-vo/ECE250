////////////////////////////////////
// Brandon Vo - ECE 250 Project 4 //
////////////////////////////////////

#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <iostream>
#include <vector>

using namespace std;

class DisjointSet {
private:
    vector<int> leader; // Leader of each vertex
    vector<int> rank;   // Rank of each vertex (height of the tree)

public:
    DisjointSet(int n);                 // Constructor
    int findSet(int vertex);            // Function to return a pointer to the representative of the set containing vertex
    void unionSets(int setA, int setB); // Function to union two disjoint sets
};

#endif