////////////////////////////////////
// Brandon Vo - ECE 250 Project 4 //
////////////////////////////////////

#include "Graph.h"
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "DisjointSet.h"
#include "illegal_exception.h"

Graph::Graph() {
    this->adj.resize(50001); // Initialize the adjacency list size
    this->mstCost = 0;
    this->mstStr = "";
}

// Runtime: O(degree(a)) where degree(a) is the degree of vertex a
// If the graph is sparse, the runtime is closer to O(1) if the edge does not exist
void Graph::insertEdge(int a, int b, int w, bool load) {
    // Illegal input. Constant time.
    if (a <= 0 || b <= 0 || a > 50000 || b > 50000 || w <= 0) {
        if (!load) {
            throw illegal_exception();
        }
        return;
    }

    // Check if edge already exists. O(degree(a))
    for (auto edge : this->adj[a]) { // Iterate through the edges of vertex a
        if (get<0>(edge) == b) {     // Check if the edge is the one to be added
            cout << "failure" << endl;
            return;
        }
    }

    // Add the edge. Constant time.
    this->adj[a].push_back(make_tuple(b, w));
    this->adj[b].push_back(make_tuple(a, w));
    this->totalEdges.push_back(make_tuple(a, b, w));

    this->mstCost = 0; // A new edge was added, so the old MST cost is no longer valid (if it even existed in the first place)
    this->mstStr = ""; // A new edge was added, so the old MST string is no longer valid (if it even existed in the first place)

    if (!load) {
        cout << "success" << endl;
    }
}

// Delete a vertex and all edges that point to it
// O(V + E) https://discuss.educative.io/t/did-not-understand-why-removing-the-vertex-would-take-o-v-e/22460
void Graph::deleteVertex(int a) {
    // Illegal input. Constant time.
    if (a <= 0 || a > 50000) {
        throw illegal_exception();
    }
    // Check if vertex is not in the graph. Constant time.
    if (this->adj.size() > 0 && this->adj[a].empty() || this->adj.size() == 0) {
        cout << "failure" << endl;
        return;
    }

    // Delete all edges from vertex a
    for (int i = 0; i < this->adj.size(); i++) { // Iterate through all vertices
        vector<tuple<int, int>> &edges = this->adj[i];
        for (int j = 0; j < edges.size(); j++) { // Iterate through all edges of vertex i
            if (get<0>(edges[j]) == a) {         // Check if the edge is the one to be deleted
                edges.erase(edges.begin() + j);  // Delete the edge
                break;
            }
        }
    }

    // Delete all edges from totalEdges that point to vertex a
    for (auto edge = this->totalEdges.begin(); edge != this->totalEdges.end();) {
        if (get<0>(*edge) == a || get<1>(*edge) == a) {
            this->totalEdges.erase(edge);
        } else {
            edge++;
        }
    }

    this->adj[a].clear(); // Delete the vertex

    this->mstCost = 0; // A vertex was deleted, so the old MST cost is no longer valid (if it even existed in the first place)
    this->mstStr = ""; // A vertex was deleted, so the old MST string is no longer valid (if it even existed in the first place)

    cout << "success" << endl;
}

// Runtime: O(degree(a)) where degree(a) is the degree of vertex a
// We need to iterate through the edges of vertex a to print the adjacent vertices
void Graph::printAdjacent(int a) {
    // Illegal input
    if (a <= 0 || a > 50000) {
        throw illegal_exception();
    }
    // Vertex not in graph
    if (this->adj.size() > 0 && this->adj[a].empty() || this->adj.size() == 0) {
        cout << "failure" << endl;
        return;
    }
    // Print the adjacent vertices. O(degree(a))
    for (auto edge : this->adj[a]) {
        cout << get<0>(edge) << " ";
    }
    cout << endl;
}

// Runtime: O(ElogE) where E is the number of edges in the graph
// Used some logic from https://www.geeksforgeeks.org/merge-sort/
void Graph::mergeSort(vector<tuple<int, int, int>> &edges, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(edges, low, mid);      // Sort first half
        mergeSort(edges, mid + 1, high); // Sort second half
        merge(edges, low, mid, high);    // Merge the two halves
    }
}

// Helper function for mergeSort
void Graph::merge(vector<tuple<int, int, int>> &edges, int low, int mid, int high) {
    vector<tuple<int, int, int>> merged;
    int i = low;
    int j = mid + 1;
    while (i <= mid && j <= high) {
        if (get<2>(edges[i]) <= get<2>(edges[j])) {
            merged.push_back(edges[i++]);
        } else {
            merged.push_back(edges[j++]);
        }
    }
    while (i <= mid) {
        merged.push_back(edges[i++]);
    }
    while (j <= high) {
        merged.push_back(edges[j++]);
    }
    // Copy merged elements back to original edges vector
    for (int k = low; k <= high; k++) {
        edges[k] = merged[k - low];
    }
}

// Citation: https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/
// Used some of the logic from the above link, aswell as the lectures to implement Kruskal's algorithm
// Dominating Runtime: O(|E|(log(|E|)) = O(|E|(log(|V|))) since E <= O(V^2), log(E) = log(V^2) = 2log(V) = O(log(V))
void Graph::kruskalMST() {
    if (this->adj.empty()) { // Graph is empty
        return;
    }

    int size = this->adj.size();

    // Sort the edges by weight in a non-decreasing order
    // Runtime: O(E(log(E))) where E is the number of edges in the graph
    mergeSort(this->totalEdges, 0, this->totalEdges.size() - 1);

    DisjointSet set(size); // Create a disjoint set to keep track of connected components

    // Iterate through sorted edges and add to MST if they do not create a cycle
    for (auto edge : this->totalEdges) {

        int a = get<0>(edge);      // Get vertex a
        int b = get<1>(edge);      // Get vertex b
        int weight = get<2>(edge); // Get weight of edge

        int setA = set.findSet(a); // Get the set of vertex a
        int setB = set.findSet(b); // Get the set of vertex b

        // Check if set a and set b are in different connected components (no cycle)
        if (setA != setB) {

            set.unionSets(setA, setB); // Union the two connected components

            this->mstCost += weight; // Add weight to cost

            // Add edge to MST string
            this->mstStr += to_string(a) + " " + to_string(b) + " " + to_string(weight) + " ";
        }
    }
}

// Get the string representation of the MST (vertex a, vertex b, weight...)
// If we have already calculated the MST and the graph has not been
// modified since, we can access the string in constant time
string Graph::getMSTStr() {
    return this->mstStr;
}

// Get the cost of the MST
// If we have already calculated the MST and the graph has not been
// modified since, we can access the cost in constant time
int Graph::getMSTCost() {
    return this->mstCost;
}