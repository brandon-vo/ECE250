////////////////////////////////////
// Brandon Vo - ECE 250 Project 1 //
////////////////////////////////////

#include "calculator.h"
#include "node.h"
using namespace std;

// Constructor: Initialize values
Calculator::Calculator() {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
    this->maxSize = 0;
}

// Destructor: Delete all nodes in linked list
Calculator::~Calculator() {
    Node *current = this->head;
    // Traverse through linked list and delete nodes
    while (current != nullptr) {
        Node *next = current->getNext(); // Store next node
        delete current;                  // Delete current node
        current = next;                  // Move current to the stored next node
    }
}

// Insert node into end of linked list
void Calculator::insert(string name, double val) {
    Node *current = head;
    while (current != nullptr) {
        // Check if the linked list already has a node with the given name
        if (current->getName() == name) {
            cout << "failure" << endl;
            return; // Exit function
        }
        current = current->getNext(); // Traverse to next node
    }

    // Create new node and set to name and val
    Node *insertNode = new Node();
    insertNode->setName(name);
    insertNode->setVal(val);

    if (!this->head) { // Empty linked list
        // Set head and tail to new data
        this->head = insertNode;
        this->tail = insertNode;
    } else {
        this->tail->setNext(insertNode); // Connect new node to the end of the list
        this->tail = insertNode;         // Update tail to the new node
    }
    this->size++; // Increase size counter
    cout << "success" << endl;
}

// Search for nodes x, y, and z, and computing the value of z based on the used command
void Calculator::compute(string x, string y, string z, string command) {
    Node *current = this->head; // Pointer to traverse through linked list
    Node *nodeX = nullptr;      // Node x
    Node *nodeY = nullptr;      // Node y
    Node *nodeZ = nullptr;      // Node z

    // Finding nodes x, y, and z and storing them
    while (current != nullptr) {
        // 3 if statements are needed instead of an if-else statement
        // because we may need to compute with the same name (Ex: x + x = x)
        if (current->getName() == x) {
            nodeX = current;
        }
        if (current->getName() == y) {
            nodeY = current;
        }
        if (current->getName() == z) {
            nodeZ = current;
        }
        current = current->getNext(); // Move pointer
    }

    // Checking if all nodes exist
    if (nodeX != nullptr && nodeY != nullptr && nodeZ != nullptr) {
        // Two options: ADD or SUB
        if (command == "ADD") {
            nodeZ->setVal(nodeX->getVal() + nodeY->getVal()); // z = x + y
        } else {
            nodeZ->setVal(nodeX->getVal() - nodeY->getVal()); // z = x - y
        }
        cout << "success" << endl;
    } else {
        // One or more nodes don't exist
        cout << "failure" << endl;
    }
}

// Remove the node with the given name
void Calculator::remove(string name) {
    Node *current = this->head;
    Node *previous = nullptr;
    while (current != nullptr) {
        if (current->getName() == name) {        // Found node to remove
            if (previous == nullptr) {           // First node in linked list is the node to remove
                this->head = current->getNext(); // Move head to the next node
            } else {
                previous->setNext(current->getNext()); // Link previous node to the node after current
            }
            delete current;    // Delete node
            current = nullptr; // Set current to nullptr
            this->size--;      // Decrease size count
            cout << "success" << endl;
            return; // Exit function
        }
        previous = current;           // Update previous
        current = current->getNext(); // Move current pointer
    }
    // Traversed through linked list and didn't find node
    cout << "failure" << endl;
}

// Print the value of the node that is being searched for
void Calculator::print(string name) {
    Node *current = this->head;
    while (current != nullptr) {
        if (current->getName() == name) {      // Found node
            cout << current->getVal() << endl; // Print value
            return;                            // Exit function
        }
        current = current->getNext();
    }
    // Traversed through linked list and didn't find node
    cout << "variable " << name << " not found" << endl;
}