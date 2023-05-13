#include "Double.h"
#include <iostream>

Double::Double(double value) : value(value) {}

void Double::print() const {
    std::cout << value;
}

std::string Double::toString() const {
    std::string str = std::to_string (value);
    str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
    str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
    return str;
}

Cell *Double::clone() const {
    return new Double(*this);
}
