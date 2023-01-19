////////////////////////////////////
// Brandon Vo - ECE 250 Project 1 //
////////////////////////////////////

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include "data.h"

// Calculator object
class Calculator {
private:
    // Linked list node
    class Node {
    public:
        Data data;
        Node* next;
    };
    Node* head;
    int size;

public:
    Calculator();
    ~Calculator();
    void insert(Data data);
    bool exists(std::string name);
    void setValue(Data data);
    double getValue(std::string name);
    void print(std::string name);
    void remove(std::string name);
    int getSize();
};

#endif