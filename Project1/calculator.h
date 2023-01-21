////////////////////////////////////
// Brandon Vo - ECE 250 Project 1 //
////////////////////////////////////

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "node.h"
#include <iostream>

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
    void insert(std::string name, double val);
    void compute(std::string x, std::string y, std::string z, std::string calculation);
    void remove(std::string name);
    void print(std::string name);
    void setMaxSize(int sizeToSet);
    int getMaxSize() const;
    int getSize() const;
};

#endif