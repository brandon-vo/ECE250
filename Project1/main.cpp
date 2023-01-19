////////////////////////////////////
// Brandon Vo - ECE 250 Project 1 //
////////////////////////////////////

#include "calculator.h"

#include <iostream>
using namespace std;

// Main function
int main() {
    Calculator* list; // Linked list object
    Data data; // Data holds the name and the value for each node
    int maxSize; // Store max size of linked list
    std::string command; // Read commands
    std::string x; // Parameter for commands
    std::string y; // Parameter for commands
    std::string z; // Parameter for commands

    // Read command
    while(cin >> command) {

        // CREATE: Create new linked list and store the max size
        if (command == "CRT") {
            list = new Calculator(); // Create new linked list
            cin >> maxSize; // Store the max size of the linked list
            cout << "success" << endl;
        } 
        
        // DEFINE: Populate the linked list with data object consisting of a name (string) and value (double)
        else if (command == "DEF") {

            double val; // Number value for each node

            // Assign parameters to input values
            cin >> x; // name input
            cin >> val; // number input

            // Assign data with the input name and value
            data.name = x;
            data.val = val;

            // Variable already exists in list or list is already at maximum capacity
            if (list->exists(x) || list->getSize() >= maxSize) {
                cout << "failure" << endl;
            } else {
                list->insert(data); // Insert data object to the end of the linked list
                cout << "success" << endl;
            }

        // ADD: Add node x + node y values and assign it to node z value
        } else if (command == "ADD") {
            // Assign name inputs
            cin >> x;
            cin >> y;
            cin >> z;

             // List doesn't contain one of the variables x, y, or z
            if (!list->exists(x) || !list->exists(y) || !list->exists(z)) {
                cout << "failure" << endl;
            } else {
                data.name = z; // Assign name
                data.val = list->getValue(x) + list->getValue(y); // Compute x + y
                list->setValue(data); // Set the value of the node in the linked list
                cout << "success" << endl;
            }
            
        // SUBTRACT: Subtract node x + node y values and assign it to node z value
        } else if (command == "SUB") {
            // Assign name inputs
            cin >> x;
            cin >> y;
            cin >> z;

             // List doesn't contain one of the variables x, y, or z
            if (!list->exists(x) || !list->exists(y) || !list->exists(z)) {
                cout << "failure" << endl;
            } else {
                data.name = z; // Assign name
                data.val = list->getValue(x) - list->getValue(y); // Compute x - y
                list->setValue(data); // Set the value of the node in the linked list
                cout << "success" << endl;
            }

        // REMOVE: Remove node with given name
        } else if (command == "REM") {
            cin >> x; // Assign name input
            if (list->exists(x)) { // Confirm node x exists in the list
                list->remove(x); // Delete the node
                cout << "success" << endl;
            } else {
                cout << "failure" << endl;
            }

        // PRINT: Print value of node name
        } else if (command == "PRT") {
            cin >> x; // Assign name input
            if (list->exists(x)) { // Confirm node x exists in the list
                list->print(x); // Print the node value
            } else {
                cout << "variable " << x << " not found" << endl;
            }

        // END: End program
        } else if (command == "END") {
            return 0;
        }
    }

    return 0; // Terminate
}