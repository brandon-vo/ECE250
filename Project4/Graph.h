////////////////////////////////////
// Brandon Vo - ECE 250 Project 4 //
////////////////////////////////////

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

class Graph {
private:
    vector<vector<tuple<int, int>>> adj; // Adjacency list
    string mstStr;                       // String representation of the minimum spanning tree
    int mstCost;                         // Cost of the minimum spanning tree
    void mergeSort(vector<tuple<int, int, int>> &edges, int low, int high);
    void merge(vector<tuple<int, int, int>> &edges, int low, int mid, int high);

public:
    Graph(int verticies = 0);                                // Constructor
    void insertEdge(int a, int b, int w, bool load = false); // Function to add an edge to graph
    void deleteVertex(int a);                                // Function to delete a vertex
    void printAdjacent(int a);                               // Function to print adjacent vertices of a vertex
    void kruskalMST();                                       // Function to compute the minimum spanning tree using Kruskal's Algorithm
    string getMSTStr();                                      // Function to get the string representation of the minimum spanning tree
    int getMSTCost();                                        // Function to get the cost of the minimum spanning tree
};

#endif