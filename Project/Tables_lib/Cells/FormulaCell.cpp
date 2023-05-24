#include "FormulaCell.h"
#include "Exceptions/RecursiveCellException.h"
#include "Exceptions/InvalidFormulaException.h"
#include "Exceptions/DivisionByZeroException.h"
#include <iostream>

FormulaCell::FormulaCell(const std::string originalString, int row, int col) : Cell(row, col, originalString) {}

void FormulaCell::printToFile(std::ostream& os) const {
    os << originalString;
}

std::string FormulaCell::toString() const {
    std::string str = std::to_string (value);
    str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
    str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
    return str;
}

Cell *FormulaCell::clone() const {
    return new FormulaCell(*this);
}

double FormulaCell::getNumericValue() const {
    return value;
}

void FormulaCell::update(const std::vector<std::vector<Cell*>> &data) {
    if (isUpdated || isCurrentlyUpdating) {
        throw RecursiveCellException(originalString, row, col);
    }

    isCurrentlyUpdating = true;

    std::stack<double> operands;
    std::stack<char> operators;

    for (int i = 1; i < originalString.length(); i++) {
        if (originalString[i] >= '0' && originalString[i] <= '9') {
            double num = 0;
            while (i < originalString.length() && originalString[i] >= '0' && originalString[i] <= '9') {
                num = num * 10 + (originalString[i] - '0');
                i++;
            }
            operands.push(num);
            i--;
        } else if (originalString[i] == '+' || originalString[i] == '-' || originalString[i] == '*' || originalString[i] == '/' || originalString[i] == '(') {
            operators.push(originalString[i]);
        } else if (originalString[i] == ')') {
            do {
                if (operators.empty() || operands.size() < 2) {
                    throw InvalidFormulaException(originalString, row, col);
                }

                calculateTwoNumbers(operands, operators);
            } while(operators.top() != '(');

            operators.pop();
        } else if (originalString[i] == 'R') {
            operands.push(getCellValue(data, i));
            i--;
        } else if (originalString[i] == ' ') {
            continue;
        } else {
            throw InvalidFormulaException(originalString, row, col);
        }
    }

    while (!operators.empty()) {
        if (operands.size() < 2) {
            throw InvalidFormulaException(originalString, row, col);
        }
        calculateTwoNumbers(operands, operators);
    }

    if (operands.size() != 1) {
        throw InvalidFormulaException(originalString, row, col);
    }

    value = operands.top();
    isUpdated = true;
    isCurrentlyUpdating = false;
}

void FormulaCell::calculateTwoNumbers(std::stack<double>& operands, std::stack<char>& operators) {
    double op2 = operands.top();
    operands.pop();
    double op1 = operands.top();
    operands.pop();
    char op = operators.top();
    operators.pop();

    double result;
    if (op == '+') {
        result = op1 + op2;
    } else if (op == '-') {
        result = op1 - op2;
    } else if (op == '*') {
        result = op1 * op2;
    } else {
        if (op2 == 0) {
            throw DivisionByZeroException(originalString, row, col);
        }
        result = op1 / op2;
    }
    operands.push(result);
}

double FormulaCell::getCellValue(const std::vector<std::vector<Cell *>> &data, int &index) {
    index++;
    int row = 0;
    while (index < originalString.length() && originalString[index] >= '0' && originalString[index] <= '9') {
        row = row * 10 + (originalString[index] - '0');
        index++;
    }

    index++;
    int col = 0;
    while (index < originalString.length() && originalString[index] >= '0' && originalString[index] <= '9') {
        col = col * 10 + (originalString[index] - '0');
        index++;
    }

    row--;
    col--;


    double cellValue = 0;
    if (row < data.size() && col < data[row].size()) {
        if (!data[row][col]->getIsUpdated()) {
            data[row][col]->update(data);
        }

        cellValue = data[row][col]->getNumericValue();
    }

    return cellValue;
}