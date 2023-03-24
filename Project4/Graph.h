#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

class Graph {
private:
    vector<vector<tuple<int, int>>> adj; // Adjacency list
    int partition(vector<tuple<int, int, int>> &edges, int low, int high);
    void quickSort(vector<tuple<int, int, int>> &edges, int low, int high);

public:
    Graph(int verticies = 0);                        // Constructor
    void insertEdge(int a, int b, int w, bool load); // Function to add an edge to graph
    void deleteVertex(int a);                        // Function to delete a vertex
    void printAdjacent(int a);                       // Function to print adjacent vertices of a vertex
    void MST(bool getCost);                          // Function to find the minimum spanning tree
};

#endif