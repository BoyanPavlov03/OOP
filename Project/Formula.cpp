#include "Formula.h"
#include <iostream>

Formula::Formula(const std::string originalString, int row, int col) : Cell(originalString, row, col) {}

void Formula::printToFile(std::ostream& os) const {
    os << originalString;
}

void Formula::print() const {
    std::cout << value;
}

std::string Formula::toString() const {
    std::string str = std::to_string (value);
    str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
    str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
    return str;
}

Cell *Formula::clone() const {
    return new Formula(*this);
}

double Formula::getNumericValue() const {
    return value;
}

bool Formula::getIsUpdated() const {
    return isUpdated;
}

void Formula::update(const std::vector<std::vector<Cell*>> &data) {
    if (isUpdated) {
        throw std::invalid_argument("Recursive cells!");
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

            double cellValue = 0;
            if (row < data.size() && col < data[row].size()) {
                Formula* formulaCell = dynamic_cast<Formula*>(data[row][col]);
                if (formulaCell != nullptr) {
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

void Formula::calculateTwoNumbers(std::stack<double>& operands, std::stack<char>& operators) {
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