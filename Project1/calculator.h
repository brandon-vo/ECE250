////////////////////////////////////
// Brandon Vo - ECE 250 Project 1 //
////////////////////////////////////

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "node.h"
#include <iostream>
using namespace std;

// Calculator object
class Calculator {
private:
    Node *head;  // Head of linked list
    Node *tail;  // Tail of linked list
    int size;    // Size of linked list
    int maxSize; // Max size of linked list

public:
    Calculator();
    ~Calculator();
    void insert(string name, double val);
    void compute(string x, string y, string z, string calculation);
    void remove(string name);
    void print(string name);
    void setMaxSize(int sizeToSet) { this->maxSize = sizeToSet; };
    int getMaxSize() const { return maxSize; };
    int getSize() const { return size; };
};

#endif