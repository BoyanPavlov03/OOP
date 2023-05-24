#include "DoubleCell.h"
#include "Exceptions/UnknownDataTypeException.h"
#include <iostream>
#include <sstream>

DoubleCell::DoubleCell(std::string str, int row, int col) : Cell(row, col, str) {
    if (!(std::istringstream(str) >> this->value >> std::ws).eof()) {
        throw UnknownDataTypeException(str, row, col);
    }
}

void DoubleCell::printToFile(std::ostream& os) const {
    os << value;
}

std::string DoubleCell::toString() const {
    std::string str = std::to_string (value);
    str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
    str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
    return str;
}

Cell *DoubleCell::clone() const {
    return new DoubleCell(*this);
}

double DoubleCell::getNumericValue() const {
    return value;
}
