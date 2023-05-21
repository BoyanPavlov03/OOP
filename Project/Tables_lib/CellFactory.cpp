#include "CellFactory.h"
#include "StringCell.h"
#include "DoubleCell.h"
#include "FormulaCell.h"
#include "IntegerCell.h"
#include "UnknownDataTypeException.h"

Cell* CellFactory::createCell(const std::string& str, int row, int col) {
    if (str[0] == '=') {
        return new FormulaCell(str, row, col);
    } else if (str[0] == '"' && str[str.size() - 1] == '"') {
        return new StringCell(str, row, col);
    } else if (str.find_first_not_of("+-0123456789") == std::string::npos) {
        return new IntegerCell(str, row, col);
    } else if (str.find_first_not_of("+-0123456789.") == std::string::npos) {
        return new DoubleCell(str, row, col);
    } else {
        throw UnknownDataTypeException(str, row, col);
    }
}