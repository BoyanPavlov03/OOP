#include "ErrorCell.h"

ErrorCell::ErrorCell(int row, int col, const std::string originalString) : Cell(row, col, originalString) {}

void ErrorCell::printToFile(std::ostream& os) const {
    std::cout << originalString << std::endl;
    os << originalString;
}

std::string ErrorCell::toString() const {
    return "ERROR";
}

Cell* ErrorCell::clone() const {
    return new ErrorCell(*this);
}

double ErrorCell::getNumericValue() const {
    return 0;
}

