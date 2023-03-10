#include <iostream>

class illegal_exception : public exception {
public:
    const char *what() const noexcept override {
        return "illegal argument";
    }
};