#include "String.h"

#include <iostream>

String::String(const std::string value) : value(value) {}

void String::print() const {
    std::cout << value;
}

std::string String::toString() const {
    return value;
}
