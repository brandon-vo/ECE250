////////////////////////////////////
// Brandon Vo - ECE 250 Project 4 //
////////////////////////////////////

#ifndef ILLLEGAL_EXCEPTION_H
#define ILLLEGAL_EXCEPTION_H

#include <iostream>
using namespace std;

// Citation: https://stackoverflow.com/questions/57627723/about-exceptions-overriding-the-standard-exception-methods
class illegal_exception : public exception {
public:
    const char *what() const noexcept {
        return "illegal argument";
    }
};

#endif