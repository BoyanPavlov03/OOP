#include "StringCell.h"
#include "Exceptions/UnknownDataTypeException.h"
#include <iostream>
#include <sstream>
#include "ConversionHelper.h"

StringCell::StringCell(const std::string originalString, int row, int col) : Cell(row, col, originalString) {
    extractString(originalString, row, col);
}

void StringCell::printToFile(std::ostream& os) const {
    os << originalString;
}

std::string StringCell::toString() const {
    return value;
}

Cell *StringCell::clone() const {
    return new StringCell(*this);
}

double StringCell::getNumericValue() const {
    try {
        return ConversionHelper::toDouble(value, row, col);
    } catch (...) {
        return 0.0;
    }
}

void StringCell::extractString(const std::string& str, int row, int col) {
    std::string result;

    for(int i = 1; i < str.size() - 1; i++) {
        if (str[i] == '\\' && i + 1 < str.size() - 1) {
            if (str[i + 1] == '"') {
                result += '"';
                i++;
            } else if (str[i + 1] == '\\') {
                result += '\\';
                i++;
            } else {
                throw UnknownDataTypeException(str, row, col);
            }
        } else {
            result += str[i];
        }
    }

    value = result;
}