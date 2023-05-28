#include "ConversionHelper.h"
#include "Exceptions/UnknownDataTypeException.h"
#include <sstream>
#include <cmath>

std::string ConversionHelper::toString(double number) {
    std::string str = std::to_string (number);
    // For some reason std::to_string adds a lot of zeros after the decimal point.
    // This is a workaround to remove them. P.S. Copied from StackOverflow :).
    str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
    str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
    return str;
}

double ConversionHelper::toDouble(std::string string, unsigned int row, unsigned int col) {
    double num;
    // For some reason std::stod doesn't throw an exception when we have more than 1 dots in the string.
    // This is a workaround to fix that. P.S. Copied from StackOverflow :).
    if (!(std::istringstream(string) >> num >> std::ws).eof()) {
        throw UnknownDataTypeException(string, row, col);
    }
    return num;
}

std::string ConversionHelper::trim(const std::string& str) {
    size_t strBegin = str.find_first_not_of(' ');
    if (strBegin == std::string::npos) {
        return "";
    }

    size_t strEnd = str.find_last_not_of(' ');
    size_t strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

double ConversionHelper::round(double number, unsigned int precision) {
    return std::round(number * std::pow(10, precision)) / std::pow(10, precision);
}