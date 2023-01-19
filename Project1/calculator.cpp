////////////////////////////////////
// Brandon Vo - ECE 250 Project 1 //
////////////////////////////////////

#include "calculator.h"
#include "data.h"
using namespace std;

// Constructor
Calculator::Calculator() {
   this->head = nullptr;
   this->size = 0;
}

// Destructor
Calculator::~Calculator() {
    Node* current = this->head;
    // Traverse through linked list and delete nodes
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

// Insert node into end of linked list
void Calculator::insert(Data newData) {
    Node* newNode = new Node;
    newNode->data = newData;
    newNode->next = nullptr;

    if (!this->head) { // Empty linked list
        this->head = newNode; // Head set to new data
    } else {
        Node* current = this->head;
        // Getting end of the linked list
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode; // Set new node the end of the linked list
    }
    this->size++; // Increase size counter
}

// Check if the linked list already has a node with the given name
bool Calculator::exists(std::string name) {
    Node* current = this->head;
    while (current != nullptr) {
        if (current->data.name == name) { // Node has been found with the same name
            return true; 
        }
        current = current->next; // Move pointer
    }
    return false; // Doesn't exist
}

// Set the value of a node
void Calculator::setValue(Data data) {
    Node* current = this->head;
    while (current != nullptr) {
        if (current->data.name == data.name) { // Found node
            current->data.val = data.val; // Set new data value
            break; // Exit loop since we have set the node value
        }
        current = current->next; // Move pointer
    }
}

// Get the value of the node with the given name
double Calculator::getValue(std::string name) {
    Node* current = this->head;
    while (current != nullptr) {
        if (current->data.name == name) { // Found node
            return current->data.val; // Get value of the node
        }
        current = current->next; // Move pointer
    }
    return 0;
}

// Print the value of the node that is being searched for
void Calculator::print(std::string name) {
    Node* current = this->head;
    while (current != nullptr) {
        if (current->data.name == name) {
            std::cout << current->data.val << endl;
            break;
        }
        current = current->next;
    }
}

// Remove the node with the given name
void Calculator::remove(std::string name) {
    Node* current = this->head;
    Node* previous = nullptr;
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
            break; // Finished. Exit loop
        }
        previous = current; // Move previous pointer
        current = current->next; // Move current pointer
    }
}

void Calculator::setSize(int size) {
    this->size = size;
}

// Get the size of the linked list 
int Calculator::getSize() {
    return this->size;
}