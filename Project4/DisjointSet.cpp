////////////////////////////////////
// Brandon Vo - ECE 250 Project 4 //
////////////////////////////////////

#include <iostream>
#include <vector>

#include "DisjointSet.h"

DisjointSet::DisjointSet(int n) {
    // Create disjoint set union for each vertex
    this->leader.resize(n);
    this->rank.resize(n);
    for (int i = 0; i < n; i++) {
        this->leader[i] = i; // Leader of each vertex is itself
        this->rank[i] = 0;   // Rank is the height of the tree
    }
}

// Recursive function to find the representative of the set containing vertex
int DisjointSet::findSet(int vertex) {
    if (this->leader[vertex] != vertex) {
        this->leader[vertex] = findSet(this->leader[vertex]);
    }
    return this->leader[vertex];
}

// Union two disjoint sets using union-by-rank
// Merge the smaller set into the larger set
void DisjointSet::unionSets(int setA, int setB) {
    if (this->rank[setA] > this->rank[setB]) {
        this->leader[setB] = setA;
    } else if (this->rank[setA] < this->rank[setB]) {
        this->leader[setA] = setB;
    } else { // If the sets are the same size, merge the second set into the first set and increment the rank of the first set
        this->leader[setB] = setA;
        this->rank[setA]++;
    }
}