////////////////////////////////////
// Brandon Vo - ECE 250 Project 4 //
////////////////////////////////////

#include <iostream>
#include <vector>

#include "DisjointSet.h"

DisjointSet::DisjointSet(int n) {
    // Create disjoint set union for each vertex
    this->parent.resize(n);
    this->rank.resize(n);
    for (int i = 0; i < n; i++) {
        this->parent[i] = i; // Parent of each vertex is itself
        this->rank[i] = 0;   // Rank is the height of the tree
    }
}

// Recursively find the root of the connected component
int DisjointSet::findParent(int vertex) {
    if (this->parent[vertex] != vertex) {
        this->parent[vertex] = findParent(this->parent[vertex]);
    }
    return this->parent[vertex];
}

// Union two disjoint sets using union-by-rank
void DisjointSet::unionSets(int parentA, int parentB) {
    if (this->rank[parentA] > this->rank[parentB]) {
        this->parent[parentB] = parentA;
    } else if (this->rank[parentA] < this->rank[parentB]) {
        this->parent[parentA] = parentB;
    } else {
        this->parent[parentB] = parentA;
        this->rank[parentA]++;
    }
}