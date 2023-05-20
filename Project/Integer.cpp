#include "Integer.h"
#include <iostream>

Integer::Integer(int value) : value(value) {}

void Integer::printToFile(std::ostream& os) const {
    os << value;
}

void Integer::print() const {
    std::cout << value;
}

std::string Integer::toString() const {
    return std::to_string(value);
}

Cell *Integer::clone() const {
    return new Integer(*this);
}

double Integer::getNumericValue() const {
    return (double)value;
}