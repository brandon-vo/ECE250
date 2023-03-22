#include "Graph.h"
#include <iostream>
#include <tuple>

#include "illegal_exception.h"

Graph::Graph() {
}

void Graph::insertEdge(int a, int b, int w, bool load) {
    if (a < 0 || b < 0 || a >= 50000 || b >= 50000 || w <= 0) {
        if (!load) {
            throw illegal_exception();
        }
        return;
    }
    // bool edge_exists = false;
    // for (auto neighbor : adj[a]) {
    //     if (neighbor == b) {
    //         edge_exists = true;
    //         break;
    //     }
    // }
    // if (edge_exists) {
    //     std::cout << "failure" << std::endl;
    //     return;
    // }
    int maxVertex = max(a, b);
    if (maxVertex >= adj.size()) {
        adj.resize(maxVertex + 1);
    }

    adj[a].push_back(make_tuple(b, w));
    adj[b].push_back(make_tuple(a, w));

    if (!load) {
        cout << "success" << endl;
    }
}

void Graph::deleteVertex(int a) {
    if (a < 0 || a >= 50000) {
        throw illegal_exception();
    }
    // if (a >= adj.size()) {
    //     cout << "failure" << endl;
    //     return;
    // }

    // // Remove the vertex a from the adjacency list of all its neighbors
    // for (auto &neighbors : adj) {
    //     neighbors.erase(remove_if(neighbors.begin(), neighbors.end(),
    //                               [a](const tuple<int, int> &neighbor) { return get<0>(neighbor) == a; }),
    //                     neighbors.end());
    // }

    // // Remove the vertex a from the graph
    // adj[a].clear();
    // adj.erase(adj.begin() + a);

    // cout << "success" << endl;
}

void Graph::printAdjacent(int a) {
    if (a < 0 || a >= 50000) {
        throw illegal_exception();
    }
    if (a >= adj.size()) {
        cout << "failure" << endl;
        return;
    }
    for (auto neighbor : adj[a]) {
        cout << get<0>(neighbor) << " ";
    }
    cout << endl;
}