#include "Integer.h"
#include "UnknownDataTypeException.h"
#include <iostream>

Integer::Integer(const std::string originalString, int row, int col) : Cell(originalString, row, col) {
    try {
        value = std::stoi(originalString);
    } catch (...) {
        throw UnknownDataTypeException(originalString, row, col);
    }
}

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