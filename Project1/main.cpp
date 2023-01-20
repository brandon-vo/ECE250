////////////////////////////////////
// Brandon Vo - ECE 250 Project 1 //
////////////////////////////////////

#include "calculator.h"

#include <iostream>
using namespace std;

// Main function
int main() {
    Calculator *list;    // Linked list object
    Data data;           // Data holds the name and the value for each node
    int maxSize;         // Max size of linked list
    std::string command; // Read commands
    std::string x;       // Parameter for commands
    std::string y;       // Parameter for commands
    std::string z;       // Parameter for commands

    // Read command
    while (cin >> command) {

        // CREATE: Create new linked list and store the max size
        if (command == "CRT") {
            list = new Calculator(); // Create new linked list
            cin >> maxSize;
            cout << "success" << endl;
        }

        // DEFINE: Populate the linked list with data object consisting of a name (string) and value (double)
        else if (command == "DEF") {

            double val; // Number value for each node

            // Assign parameters to input values
            cin >> x;   // name input
            cin >> val; // number input

            // Assign data with the input name and value
            data.name = x;
            data.val = val;

            list->insert(data, maxSize); // Insert data object to the end of the linked list

            // ADD/SUB: Add/Subtract nodes x and y and assign it to node z value
        } else if (command == "ADD" || command == "SUB") {
            // Assign name inputs
            cin >> x;
            cin >> y;
            cin >> z;

            list->compute(x, y, z, command); // Compute the nodes

            // REMOVE: Delete node from linked list
        } else if (command == "REM") {
            cin >> x;        // Assign name input
            list->remove(x); // Delete the node

            // PRINT: Print value of node name
        } else if (command == "PRT") {
            cin >> x;       // Assign name input
            list->print(x); // Print the node value

            // END: Exit loop
        } else if (command == "END") {
            break;
        }
    }
    delete list; // Delete linked list calculator to prevent leaks
    return 0;    // Terminate
}