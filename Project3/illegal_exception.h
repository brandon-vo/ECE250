#include <iostream>

class illegal_exception : public std::exception {
public:
    const char *what() const noexcept override {
        return "illegal argument";
    }
};