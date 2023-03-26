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
                    g.insertEdge(input1, input2, input3, false);
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
            } else if (command == "MST") {
                g.kruskalMST(false);
                cout << endl;
            } else if (command == "COST") {
                g.kruskalMST(true);
            } else if (command == "END") {
                break;
            }
        }
    }
}