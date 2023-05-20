#include "CellFactory.h"
#include "String.h"
#include "Double.h"
#include "Formula.h"
#include "Integer.h"
#include "UnknownDataTypeException.h"

Cell* CellFactory::createCell(const std::string& str, int row, int col) {
    if (str[0] == '=') {
        return new Formula(str, row, col);
    } else if (str[0] == '"' && str[str.size() - 1] == '"') {
        return new String(str, row, col);
    } else if (str.find_first_not_of("+-0123456789") == std::string::npos) {
        return new Integer(str, row, col);
    } else if (str.find_first_not_of("+-0123456789.") == std::string::npos) {
        return new Double(str, row, col);
    } else {
        throw UnknownDataTypeException(str, row, col);
    }
}