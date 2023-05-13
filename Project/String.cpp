#include "String.h"

#include <iostream>

String::String(const std::string value) : value(value) {}

void String::print() const {
    std::cout << value;
}

std::string String::toString() const {
    return value;
}

Cell *String::clone() const {
    return new String(*this);
}

double String::getValue() const {
    double num;
    try {
        num = stod(value);
    } catch (...) {
        return 0;
    }
    return num;
}