#include "Cell.h"

Cell::Cell(int row, int col, std::string originalString) : originalString(originalString), row(row), col(col) {}

std::ostream &operator<<(std::ostream &os, const Cell &cell) {
    cell.printToFile(os);
    return os;
}

std::string Cell::trim(const std::string& str) {
    const auto strBegin = str.find_first_not_of(' ');
    if (strBegin == std::string::npos)
        return "";

    const auto strEnd = str.find_last_not_of(' ');
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

bool Cell::getIsUpdated() const {
    return isUpdated;
}

void Cell::setIsUpdated(bool _isUpdated) {
    isUpdated = _isUpdated;
}
