#include "Graph.h"
#include <iostream>
#include <tuple>
#include <vector>

#include "illegal_exception.h"

Graph::Graph(int vertices) {
    adj.resize(vertices); // Initialize the adjacency list size
}

void Graph::insertEdge(int a, int b, int w, bool load) {
    // Illegal input
    if (a <= 0 || b <= 0 || a > 50000 || b > 50000 || w <= 0) {
        if (!load) {
            throw illegal_exception();
        }
        return;
    }
    int currentSize = adj.size();
    int maxVertex = max(a, b);
    if (maxVertex >= adj.size()) { // Resize the adjacency list if necessary
        adj.resize(maxVertex + 1);
    }

    // Check if edge already exists
    for (auto edge : adj[a]) {
        if (get<0>(edge) == b) {
            cout << "failure" << endl;
            adj.resize(currentSize);
            return;
        }
    }

    // Add the edge
    adj[a].push_back(make_tuple(b, w));
    adj[b].push_back(make_tuple(a, w));

    if (!load) {
        cout << "success" << endl;
    }
}

void Graph::deleteVertex(int a) {
    // Illegal input
    if (a <= 0 || a > 50000) {
        throw illegal_exception();
    }
    // Vertex not in graph
    if (adj.size() > 0 && adj[a].empty() || adj.size() == 0) {
        cout << "failure" << endl;
        return;
    }
    // Remove all edges containing vertex a
    for (int i = 0; i < adj.size(); i++) {
        // Skip vertex a
        if (i == a) {
            continue;
        }
        // Remove the edge from i to a
        auto it = adj[i].begin();
        while (it != adj[i].end()) {
            if (get<0>(*it) == a) {
                it = adj[i].erase(it);
            } else {
                ++it;
            }
        }
    }

    // Clear the adjacency list for vertex a
    adj[a].clear();
    cout << "success" << endl;
}

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
    // Print the adjacent vertices
    for (auto edge : adj[a]) {
        cout << get<0>(edge) << " ";
    }
    cout << endl;
}

int Graph::partition(vector<tuple<int, int, int>> &edges, int low, int high) {
    tuple<int, int, int> pivot = edges[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (get<2>(edges[j]) < get<2>(pivot)) {
            i++;
            swap(edges[i], edges[j]);
        }
    }
    swap(edges[i + 1], edges[high]);
    return i + 1;
}

void Graph::quickSort(vector<tuple<int, int, int>> &edges, int low, int high) {
    if (low < high) {
        int pivot = partition(edges, low, high);
        quickSort(edges, low, pivot - 1);
        quickSort(edges, pivot + 1, high);
    }
}

void Graph::MST(bool getCost) {
    if (adj.empty()) {
        if (getCost) {
            cout << "cost is 0" << endl;
        } else {
            cout << "failure";
        }
        return;
    }

    int n = adj.size();
    // Create a vector of edges (source, destination, weight)
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < n; i++) {
        for (auto edge : adj[i]) {
            int j = get<0>(edge);
            int w = get<1>(edge);
            edges.push_back(make_tuple(i, j, w));
        }
    }

    // Sort edges by weight
    quickSort(edges, 0, edges.size() - 1);

    // Initialize parent array and rank array for union-find
    vector<int> parent(n);
    vector<int> rank(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int cost = 0;
    vector<tuple<int, int>> mst;
    // Iterate through sorted edges and add to MST if they do not create a cycle
    for (auto edge : edges) {
        int a = get<0>(edge);
        int b = get<1>(edge);
        int weight = get<2>(edge);

        // Find parent of u and v using union-find
        int pa = parent[a];
        int pb = parent[b];
        while (pa != parent[pa]) {
            parent[pa] = parent[parent[pa]];
            pa = parent[pa];
        }
        while (pb != parent[pb]) {
            parent[pb] = parent[parent[pb]];
            pb = parent[pb];
        }

        // Check if u and v are in different connected components
        if (pa != pb) {
            // Add edge to MST
            mst.push_back(make_tuple(a, b));
            cost += weight;

            // Union u and v using rank
            if (rank[pa] > rank[pb]) {
                parent[pb] = pa;
            } else if (rank[pa] < rank[pb]) {
                parent[pa] = pb;
            } else {
                parent[pb] = pa;
                rank[pa]++;
            }
            if (!getCost) {
                cout << get<0>(edge) << " " << get<1>(edge) << " " << get<2>(edge) << " ";
            }
        }
    }

    // Print MST cost if requested
    if (getCost) {
        cout << "cost is " << cost << endl;
    }
}