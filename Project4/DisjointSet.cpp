////////////////////////////////////
// Brandon Vo - ECE 250 Project 4 //
////////////////////////////////////

#include <iostream>
#include <vector>

#include "DisjointSet.h"

DisjointSet::DisjointSet(int n) {
    // Create disjoint set union for each vertex
    parent.resize(n);
    rank.resize(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i; // Parent of each vertex is itself
        rank[i] = 0;   // Rank is the height of the tree
    }
}

// Recursively find the root of the connected component
int DisjointSet::findParent(int vertex) {
    if (parent[vertex] != vertex) {
        parent[vertex] = findParent(parent[vertex]);
    }
    return parent[vertex];
}

// Union two disjoint sets using union-by-rank
void DisjointSet::unionSets(int parentA, int parentB) {
    if (rank[parentA] > rank[parentB]) {
        parent[parentB] = parentA;
    } else if (rank[parentA] < rank[parentB]) {
        parent[parentA] = parentB;
    } else {
        parent[parentB] = parentA;
        rank[parentA]++;
    }
}