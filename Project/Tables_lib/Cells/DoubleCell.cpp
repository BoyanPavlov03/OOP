#include "DoubleCell.h"
#include "Exceptions/UnknownDataTypeException.h"
#include "ConversionHelper.h"

DoubleCell::DoubleCell(std::string str, int row, int col) : Cell(row, col, str) {
    value = ConversionHelper::toDouble(str, row, col);
}

void DoubleCell::printToFile(std::ostream& os) const {
    os << value;
}

std::string DoubleCell::toString() const {
    return ConversionHelper::toString(value);
}

Cell *DoubleCell::clone() const {
    return new DoubleCell(*this);
}

double DoubleCell::getNumericValue() const {
    return value;
}
