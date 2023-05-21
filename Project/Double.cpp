#include "Double.h"
#include "UnknownDataTypeException.h"
#include <iostream>
#include <sstream>

Double::Double(std::string str, int row, int col) : Cell(row, col, str) {
    if (!(std::istringstream(str) >> this->value >> std::ws).eof()) {
        throw UnknownDataTypeException(str, row, col);
    }
}

void Double::printToFile(std::ostream& os) const {
    os << value;
}

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

double Double::getNumericValue() const {
    return value;
}
