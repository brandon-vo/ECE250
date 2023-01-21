////////////////////////////////////
// Brandon Vo - ECE 250 Project 1 //
////////////////////////////////////

#ifndef NODE_H
#define NODE_H

#include <iostream>

// Linked list node
class Node {
private:
    std::string name; // Name of node (the name we define the node to be)
    double val;       // Value of node (the number assigned to the node)
    Node *next;       // Pointer to next node
public:
    Node(std::string name, double val) : name(name), val(val), next(nullptr){}; // Constructor
    void setNext(Node *next) { this->next = next; };                            // Set next node
    Node *getNext() const { return next; };                                     // Get next node
    std::string getName() const { return name; };                               // Get name of node
    void setVal(double val) { this->val = val; };                               // Set value of node
    double getVal() const { return val; };                                      // Get value of node
};

#endif