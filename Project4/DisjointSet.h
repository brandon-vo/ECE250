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
    vector<int> parent; // Parent of each vertex
    vector<int> rank;   // Rank of each vertex (height of the tree)

public:
    DisjointSet(int n);                       // Constructor
    int findParent(int vertex);               // Function to find the parent of a vertex
    void unionSets(int parentA, int parentB); // Function to union two disjoint sets
};

#endif