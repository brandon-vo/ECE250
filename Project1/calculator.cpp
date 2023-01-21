////////////////////////////////////
// Brandon Vo - ECE 250 Project 1 //
////////////////////////////////////

#include "calculator.h"
#include "node.h"
using namespace std;

// Constructor
Calculator::Calculator() {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
    this->maxSize = 0;
}

// Destructor
Calculator::~Calculator() {
    Node *current = this->head;
    // Traverse through linked list and delete nodes
    while (current != nullptr) {
        Node *next = current->getNext();
        delete current;
        current = next;
    }
}

// Insert node into end of linked list
void Calculator::insert(std::string name, double val) {
    Node *current = head;
    while (current != nullptr) {
        // Check if the linked list already has a node with the given name
        if (current->getName() == name) {
            std::cout << "failure" << std::endl;
            return; // Exit function
        }
        current = current->getNext(); // Traverse to next node
    }

    // Create new node and set to name and val
    Node *newNode = new Node();
    newNode->setName(name);
    newNode->setVal(val);

    if (!this->head) { // Empty linked list
        // Set head and tail to new data
        this->head = newNode;
        this->tail = newNode;
    } else {
        // WRITE CODE HERE
        this->tail->setNext(newNode); // Set tail's next to new node
        this->tail = newNode;         // Update tail to new node
    }
    this->size++; // Increase size counter
    std::cout << "success" << std::endl;
}

// Search for nodes x, y, and z, and computing the value of z based on the used command
void Calculator::compute(std::string x, std::string y, std::string z, std::string calculation) {
    Node *current = this->head; // Pointer to traverse through linked list
    Node *nodeX = nullptr;      // Node x
    Node *nodeY = nullptr;      // Node y
    Node *nodeZ = nullptr;      // Node z
    while (current != nullptr) {
        // Finding nodes x, y, and z and storing them
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
        if (calculation == "ADD") {
            nodeZ->setVal(nodeX->getVal() + nodeY->getVal()); // z = x + y
        } else {
            nodeZ->setVal(nodeX->getVal() - nodeY->getVal()); // z = x - y
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
        if (current->getName() == name) {    // Found node to remove
            this->head = current->getNext(); // Set head to next
            delete current;                  // Delete node
            current = nullptr;
            this->size--; // Decrease size count
            std::cout << "success" << std::endl;
            return; // Exit function
        }
        previous = current;           // Move previous pointer
        current = current->getNext(); // Move current pointer
    }
    // Traversed through linked list and didn't find node
    std::cout << "failure" << std::endl;
}

// Print the value of the node that is being searched for
void Calculator::print(std::string name) {
    Node *current = this->head;
    while (current != nullptr) {
        if (current->getName() == name) {                // Found node
            std::cout << current->getVal() << std::endl; // Print value
            return;                                      // Exit function
        }
        current = current->getNext();
    }
    // Traversed through linked list and didn't find node
    std::cout << "variable " << name << " not found" << std::endl;
}

// Set the maximum size of the linked list
void Calculator::setMaxSize(int sizeToSet) {
    this->maxSize = sizeToSet;
}

// Get the maximum size of the linked list
int Calculator::getMaxSize() const {
    return this->maxSize;
}

// Get the current size of the linked list
int Calculator::getSize() const {
    return this->size;
}