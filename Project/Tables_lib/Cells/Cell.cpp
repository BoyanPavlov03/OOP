#include "Cell.h"

Cell::Cell(int row, int col, std::string originalString) : originalString(originalString), row(row), col(col) {}

std::ostream &operator<<(std::ostream &os, const Cell &cell) {
    cell.printToFile(os);
    return os;
}

std::string Cell::getOriginalString() const {
    return originalString;
}