////////////////////////////////////
// Brandon Vo - ECE 250 Project 4 //
////////////////////////////////////

#include "Graph.h"
#include "illegal_exception.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    Graph g;         // Create a graph
    string command;  // Command to be executed
    string fileName; // Name of file to be loaded
    int input1;      // Input parameter
    int input2;      // Input parameter
    int input3;      // Input parameter
    while (cin >> command) {
        if (command == "LOAD") {
            cin >> fileName;
            ifstream fin(fileName.c_str());
            fin >> input1;
            while (fin >> input1 >> input2 >> input3) {
                g.insertEdge(input1, input2, input3, true);
            }
            fin.close();
            cout << "success" << endl;
        } else {
            if (command == "INSERT") {
                cin >> input1;
                cin >> input2;
                cin >> input3;
                try {
                    g.insertEdge(input1, input2, input3);
                } catch (illegal_exception &e) {
                    cout << e.what() << endl;
                }
            } else if (command == "PRINT") {
                cin >> input1;
                try {
                    g.printAdjacent(input1);
                } catch (illegal_exception &e) {
                    cout << e.what() << endl;
                }
            } else if (command == "DELETE") {
                cin >> input1;
                try {
                    g.deleteVertex(input1);
                } catch (illegal_exception &e) {
                    cout << e.what() << endl;
                }
            } else if (command == "MST") { // Best case: O(1), Average/Worst Case: O(|E|log|V|)
                // If the MST has already been ran and theres no modifications to the graph, theres no need to recalculate
                // If mstStr is not empty, it means the MST has already been calculated since we would have reset mstStr to ""
                // when we add a new edge or delete a vertex from the graph
                if (g.getMSTStr() == "") {
                    g.kruskalMST();
                }
                // After calculating the MST, print it out
                if (g.getMSTStr() != "") {
                    cout << g.getMSTStr() << endl;
                } else { // If we reach here, it means the adjacency list is empty so we can't calculate the MST
                    cout << "failure" << endl;
                }
            } else if (command == "COST") { // Best case: O(1), Average/Worst Case: O(|E|log|V|)
                // If the cost already calculated and theres no modifications to the graph, theres no need to recalculate
                // If mstCost isnt 0, it means the cost has already been calculated since we would have reset mstCost to 0
                // when we add a new edge or delete a vertex from the graph
                if (g.getMSTCost() == 0) {
                    g.kruskalMST();
                }
                cout << "cost is " << g.getMSTCost() << endl; // O(1)
            } else if (command == "END") {
                break;
            }
        }
    }
}