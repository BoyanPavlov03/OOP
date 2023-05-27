#include "ConversionHelper.h"
#include "Exceptions/UnknownDataTypeException.h"
#include <sstream>

std::string ConversionHelper::toString(double number) {
    std::string str = std::to_string (number);
    str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
    str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
    return str;
}

double ConversionHelper::toDouble(std::string string, unsigned int row, unsigned int col) {
    double num;
    if (!(std::istringstream(string) >> num >> std::ws).eof()) {
        throw UnknownDataTypeException(string, row, col);
    }
    return num;
}

std::string ConversionHelper::trim(const std::string& str) {
    const auto strBegin = str.find_first_not_of(' ');
    if (strBegin == std::string::npos)
        return "";

    const auto strEnd = str.find_last_not_of(' ');
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}