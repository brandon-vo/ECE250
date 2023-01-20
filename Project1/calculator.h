////////////////////////////////////
// Brandon Vo - ECE 250 Project 1 //
////////////////////////////////////

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "data.h"
#include <iostream>

// Calculator object
class Calculator {
private:
    // Linked list node
    class Node {
    public:
        Data data;  // Data object
        Node *next; // Pointer to next node
    };
    Node *head; // Head of linked list
    Node *tail; // Tail of linked list
    int size;   // Size of linked list

public:
    Calculator();
    ~Calculator();
    void insert(Data data, int maxSize);
    void compute(std::string x, std::string y, std::string z, std::string calculation);
    void remove(std::string name);
    void print(std::string name);
    int getSize();
};

#endif