#include "IntegerCell.h"
#include "Exceptions/UnknownDataTypeException.h"

IntegerCell::IntegerCell(const std::string originalString, int row, int col) : Cell(row, col, originalString) {
    try {
        value = std::stoi(originalString);
    } catch (...) {
        throw UnknownDataTypeException(originalString, row, col);
    }
}

void IntegerCell::printToFile(std::ostream& os) const {
    os << value;
}

std::string IntegerCell::toString() const {
    return std::to_string(value);
}

Cell *IntegerCell::clone() const {
    return new IntegerCell(*this);
}

double IntegerCell::getNumericValue() const {
    return (double)value;
}