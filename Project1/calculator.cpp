////////////////////////////////////
// Brandon Vo - ECE 250 Project 1 //
////////////////////////////////////

#include "calculator.h"
#include "data.h"
using namespace std;

// Constructor
Calculator::Calculator() {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

// Destructor
Calculator::~Calculator() {
    Node *current = this->head;
    // Traverse through linked list and delete nodes
    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

// Insert node into end of linked list
void Calculator::insert(Data newData, int maxSize) {
    if (this->size == maxSize) { // Check if linked list is full
        std::cout << "failure" << std::endl;
        return; // Exit function
    }

    Node *current = head;
    while (current != nullptr) {
        // Check if the linked list already has a node with the given name
        if (current->data.name == newData.name) {
            std::cout << "failure" << std::endl;
            return; // Exit function
        }
        current = current->next; // Traverse to next node
    }

    // Create new node and set to new data
    Node *newNode = new Node();
    newNode->data = newData;

    if (!this->head) { // Empty linked list
        // Set head and tail to new data
        this->head = newNode;
        this->tail = newNode;
    } else {
        tail->next = newNode; // Set new node to the end of the linked list
        tail = newNode;       // Update tail pointer to the new node
    }
    this->size++; // Increase size counter
    std::cout << "success" << std::endl;
}

void Calculator::compute(std::string x, std::string y, std::string z, std::string calculation) {
    Node *current = this->head; // Pointer to traverse through linked list
    Node *nodeX = nullptr;      // Node x
    Node *nodeY = nullptr;      // Node y
    Node *nodeZ = nullptr;      // Node z
    while (current != nullptr) {
        // Finding nodes x, y, and z and storing them
        if (current->data.name == x) {
            nodeX = current;
        }
        if (current->data.name == y) {
            nodeY = current;
        }
        if (current->data.name == z) {
            nodeZ = current;
        }
        current = current->next; // Move pointer
    }

    // Checking if all nodes exist
    if (nodeX != nullptr && nodeY != nullptr && nodeZ != nullptr) {
        // Two options: ADD or SUB
        if (calculation == "ADD") {
            nodeZ->data.val = nodeX->data.val + nodeY->data.val; // z = x + y
        } else {
            nodeZ->data.val = nodeX->data.val - nodeY->data.val; // z = x - y
        }
        std::cout << "success" << std::endl;
    } else {
        // One or more nodes don't exist
        std::cout << "failure" << std::endl;
    }
}

// Remove the node with the given name
void Calculator::remove(std::string name) {
    Node *current = this->head;
    Node *previous = nullptr;
    while (current != nullptr) {
        if (current->data.name == name) { // Found node to remove
            if (previous != nullptr) {
                previous->next = current->next; // Set previous to next
            } else {
                this->head = current->next; // Set head to next
            }
            delete current; // Delete node
            current = nullptr;
            this->size--; // Decrease size count
            std::cout << "success" << std::endl;
            return; // Exit function
        }
        previous = current;      // Move previous pointer
        current = current->next; // Move current pointer
    }
    // Traversed through linked list and didn't find node
    std::cout << "failure" << std::endl;
}

// Print the value of the node that is being searched for
void Calculator::print(std::string name) {
    Node *current = this->head;
    while (current != nullptr) {
        if (current->data.name == name) {                // Found node
            std::cout << current->data.val << std::endl; // Print value
            return;                                      // Exit function
        }
        current = current->next;
    }
    // Traversed through linked list and didn't find node
    std::cout << "variable " << name << " not found" << std::endl;
}

// Get the current size of the linked list
int Calculator::getSize() {
    return this->size;
}