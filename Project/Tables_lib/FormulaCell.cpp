#include "FormulaCell.h"
#include "RecursiveCellException.h"
#include <iostream>

FormulaCell::FormulaCell(const std::string originalString, int row, int col) : Cell(row, col, originalString) {}

void FormulaCell::printToFile(std::ostream& os) const {
    os << originalString;
}

void FormulaCell::print() const {
    std::cout << value;
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

bool FormulaCell::getIsUpdated() const {
    return isUpdated;
}

void FormulaCell::setIsUpdated(bool isUpdated) {
    this->isUpdated = isUpdated;
}

void FormulaCell::update(const std::vector<std::vector<Cell*>> &data) {
    if (isUpdated) {
        throw RecursiveCellException(originalString, row, col);
    }

    std::stack<double> operands;
    std::stack<char> operators;

    for (int i = 0; i < originalString.length(); i++) {
        if (originalString[i] >= '0' && originalString[i] <= '9') {
            double num = 0;
            while (i < originalString.length() && originalString[i] >= '0' && originalString[i] <= '9') {
                num = num * 10 + (originalString[i] - '0');
                i++;
            }
            operands.push(num);
            i--;
        } else if (originalString[i] == '+' || originalString[i] == '-' || originalString[i] == '*' || originalString[i] == '/') {
            operators.push(originalString[i]);
        } else if (originalString[i] == '(') {
            operators.push(originalString[i]);
        } else if (originalString[i] == ')') {
            do {
                if (operators.empty() || operands.size() < 2) {
                    throw std::invalid_argument("Invalid formula!");
                }

                calculateTwoNumbers(operands, operators);
            } while(operators.top() != '(');

            operators.pop();
        } else if (originalString[i] == 'R') {

            i++;
            int row = 0;
            while (i < originalString.length() && originalString[i] >= '0' && originalString[i] <= '9') {
                row = row * 10 + (originalString[i] - '0');
                i++;
            }

            i++;
            int col = 0;
            while (i < originalString.length() && originalString[i] >= '0' && originalString[i] <= '9') {
                col = col * 10 + (originalString[i] - '0');
                i++;
            }

            row--;
            col--;


            // TODO: too many nested if's
            double cellValue = 0;
            if (row < data.size() && col < data[row].size() && data[row][col] != nullptr) {
                FormulaCell* formulaCell = dynamic_cast<FormulaCell*>(data[row][col]);
                if (formulaCell != nullptr) {
                    if (formulaCell == this) {
                        throw RecursiveCellException(originalString, row, col);
                    }

                    if (!formulaCell->isUpdated) {
                        formulaCell->update(data);
                    }
                }

                cellValue = data[row][col]->getNumericValue();
            }

            operands.push(cellValue);
            i--;
        }
    }

    while (!operators.empty()) {
        calculateTwoNumbers(operands, operators);
    }

    value = operands.top();
    isUpdated = true;
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
        result = op1 / op2;
    }
    operands.push(result);
}