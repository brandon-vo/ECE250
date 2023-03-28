////////////////////////////////////
// Brandon Vo - ECE 250 Project 4 //
////////////////////////////////////

#include "Graph.h"
#include <iostream>
#include <tuple>
#include <vector>

#include "DisjointSet.h"
#include "illegal_exception.h"

Graph::Graph(int vertices) {
    adj.resize(vertices); // Initialize the adjacency list size
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

    // Constant time
    int maxVertex = max(a, b);
    if (maxVertex >= adj.size()) { // Resize the adjacency list if necessary
        adj.resize(maxVertex + 1);
    }

    // Check if edge already exists. O(degree(a))
    for (auto edge : adj[a]) {   // Iterate through the edges of vertex a
        if (get<0>(edge) == b) { // Check if the edge is the one to be added
            cout << "failure" << endl;
            return;
        }
    }

    // Add the edge. Constant time.
    adj[a].push_back(make_tuple(b, w));
    adj[b].push_back(make_tuple(a, w));

    if (!load) {
        cout << "success" << endl;
    }
}

// Runtime: O(|V| + |E|) where |V| is the number of vertices and |E| is the number of edges
void Graph::deleteVertex(int a) {
    // Illegal input. Constant time.
    if (a <= 0 || a > 50000) {
        throw illegal_exception();
    }
    // Check if vertex is not in the graph. Constant time.
    if (adj.size() > 0 && adj[a].empty() || adj.size() == 0) {
        cout << "failure" << endl;
        return;
    }
    int numVertices = adj.size();
    for (int i = 0; i < numVertices; i++) { // Iterate through all vertices
        if (i == a) {
            adj[i].clear(); // Clear the vertex to be deleted
        }
        int numEdges = adj[i].size();
        for (int j = 0; j < numEdges; j++) {      // Iterate through all edges of the vertex
            if (get<0>(adj[i][j]) == a) {         // Check if the edge is the one to be removed
                adj[i].erase(adj[i].begin() + j); // Remove the edge to the deleted vertex
                break;
            }
        }
    }
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
    if (adj.size() > 0 && adj[a].empty() || adj.size() == 0) {
        cout << "failure" << endl;
        return;
    }
    // Print the adjacent vertices. O(degree(a))
    for (auto edge : adj[a]) {
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
// Used some of the logic from the above link to implement Kruskal's algorithm
// Dominating Runtime: O(E(log(E)) = O(E(log(V))) since E <= O(V^2), log(E) = log(V^2) = 2log(V) = O(log(V))
void Graph::kruskalMST(bool getCost) {
    if (adj.empty()) { // Graph is empty
        if (getCost) {
            cout << "cost is 0" << endl;
        } else {
            cout << "failure";
        }
        return;
    }

    int n = adj.size();

    // Create a vector of all edges in the graph
    // Runtime: O(E) where E is the number of edges in the graph
    vector<tuple<int, int, int>> totalEdges; // (vertex a, vertex b, weight)
    for (int a = 0; a < n; a++) {            // Iterate through each vertex
        for (auto edge : adj[a]) {           // Iterate through the edges of each vertex a
            int b = get<0>(edge);
            int weight = get<1>(edge);
            totalEdges.push_back(make_tuple(a, b, weight)); // Add the edge to the vector
        }
    }

    // Sort the edges by weight in a non-decreasing order
    // Runtime: O(E(log(E))) where E is the number of edges in the graph
    mergeSort(totalEdges, 0, totalEdges.size() - 1);

    DisjointSet set(n); // Create a disjoint set to keep track of connected components

    int mstCost = 0;                  // Store the cost of the MST
    vector<tuple<int, int>> mstEdges; // Store the edges of the MST

    // Iterate through sorted edges and add to MST if they do not create a cycle
    for (auto edge : totalEdges) {

        int a = get<0>(edge);      // Get vertex a
        int b = get<1>(edge);      // Get vertex b
        int weight = get<2>(edge); // Get weight of edge

        // Find parent of a and b using union-find
        int parentA = set.findParent(a);
        int parentB = set.findParent(b);

        // Check if a and b are in different connected components (no cycle)
        if (parentA != parentB) {
            mstEdges.push_back(make_tuple(a, b)); // Add edge to MST
            mstCost += weight;                    // Add weight to cost

            // Union the two connected components
            set.unionSets(parentA, parentB);

            if (!getCost) { // Print MST as we go if requested
                cout << get<0>(edge) << " " << get<1>(edge) << " " << get<2>(edge) << " ";
            }
        }
    }

    // Print MST cost if requested
    if (getCost) {
        cout << "cost is " << mstCost << endl;
    }
}