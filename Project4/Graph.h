#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

class Graph {
private:
    vector<vector<tuple<int, int>>> adj; // Adjacency matrix 
public:
    Graph();                                         // Constructor
    void insertEdge(int a, int b, int w, bool load); // Function to add an edge to graph
    void deleteVertex(int a);                        // Function to delete a vertex
    void printAdjacent(int a);                       // Function to print adjacent vertices of a vertex
};

#endif