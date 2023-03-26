////////////////////////////////////
// Brandon Vo - ECE 250 Project 4 //
////////////////////////////////////

#include "Graph.h"
#include <iostream>
#include <tuple>
#include <vector>

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

// Runtime: O(V) where V is the number of vertices in the graph
// The maximum degree of a node is O(V), so O(degree(a) * E) = O(V * E)
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

    // Remove all edges containing vertex a
    for (auto edge : adj[a]) {                                                       // O(degree(a)) where degree(a) is the degree of vertex a
        int i = get<0>(edge);                                                        // Vertex connected to a
        int weight = get<1>(edge);                                                   // Weight of the edge
        for (auto iterator = adj[i].begin(); iterator != adj[i].end(); iterator++) { // O(E) where E is the number of edges in the graph
            if (get<0>(*iterator) == a && get<1>(*iterator) == weight) {             // Check if the edge is the one to be removed
                adj[i].erase(iterator);                                              // Remove the edge
                break;
            }
        }
    }

    // Clear the adjacency list for vertex a
    adj[a].clear();
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

void Graph::mergeSort(vector<tuple<int, int, int>> &edges, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(edges, low, mid);      // Sort first half
        mergeSort(edges, mid + 1, high); // Sort second half

        // Merge the two sorted halves
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

        // Copy merged elements back to original array
        for (int k = low; k <= high; k++) {
            edges[k] = merged[k - low];
        }
    }
}

// Recursively find the root of the connected component
int Graph::findParent(vector<int> &parent, int vertex) {
    if (parent[vertex] != vertex) {
        parent[vertex] = findParent(parent, parent[vertex]);
    }
    return parent[vertex];
}

// Citation: https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/
// Used some of the logic from the above link to implement Kruskal's algorithm
// Runtime: O(E(log(E)) = O(E(log(V))) since E <= O(V^2), log(E) = log(V^2) = 2log(V) = O(log(V))
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

    // Create disjoint set union for each vertex
    vector<int> parent(n);
    vector<int> rank(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i; // Parent of each vertex is itself
        rank[i] = 0;   // Rank is the height of the tree
    }

    int mstCost = 0;                  // Store the cost of the MST
    vector<tuple<int, int>> mstEdges; // Store the edges of the MST
    // Iterate through sorted edges and add to MST if they do not create a cycle
    for (auto edge : totalEdges) {
        int a = get<0>(edge);
        int b = get<1>(edge);
        int weight = get<2>(edge);

        // Find parent of a and b using union-find
        int parentA = findParent(parent, a);
        int parentB = findParent(parent, b);

        // Check if a and b are in different connected components (no cycle)
        if (parentA != parentB) {
            mstEdges.push_back(make_tuple(a, b)); // Add edge to MST
            mstCost += weight;                    // Add weight to cost

            // Union the two connected components
            if (rank[parentA] > rank[parentB]) {
                parent[parentB] = parentA;
            } else if (rank[parentA] < rank[parentB]) {
                parent[parentA] = parentB;
            } else {
                parent[parentB] = parentA;
                rank[parentA]++;
            }
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