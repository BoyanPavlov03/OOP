#include "String.h"
#include "UnknownDataTypeException.h"
#include <iostream>

String::String(const std::string originalString, int row, int col) : originalString(originalString) {
    extractString(originalString, row, col);
}

void String::printToFile(std::ostream& os) const {
    os << originalString;
}

void String::print() const {
    std::cout << value;
}

std::string String::toString() const {
    return value;
}

Cell *String::clone() const {
    return new String(*this);
}

double String::getNumericValue() const {
    double num;
    try {
        num = stod(value);
    } catch (...) {
        return 0;
    }
    return num;
}

void String::extractString(const std::string& str, int row, int col) {
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
        } else if (str[i] == '\\' && i + 1 >= str.size() - 1) {
            throw UnknownDataTypeException(str, row, col);
        } else {
            result += str[i];
        }
    }

    value = result;
}