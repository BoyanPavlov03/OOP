#include "Formula.h"
#include <iostream>

Formula::Formula(double value, const std::string formula) : value(value), formula(formula) {}

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

double Formula::getValue() const {
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

    for (int i = 0; i < formula.length(); i++) {
        if (formula[i] >= '0' && formula[i] <= '9') {
            double num = 0;
            while (i < formula.length() && formula[i] >= '0' && formula[i] <= '9') {
                num = num * 10 + (formula[i] - '0');
                i++;
            }
            operands.push(num);
            i--;
        } else if (formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/') {
            operators.push(formula[i]);
        } else if (formula[i] == '(') {
            operators.push(formula[i]);
        } else if (formula[i] == ')') {
            do {
                if (operators.empty() || operands.size() < 2) {
                    throw std::invalid_argument("Invalid formula!");
                }

                calculateTwoNumbers(operands, operators);
            } while(operators.top() != '(');

            operators.pop();
        } else if (formula[i] == 'R') {

            i++;
            int row = 0;
            while (i < formula.length() && formula[i] >= '0' && formula[i] <= '9') {
                row = row * 10 + (formula[i] - '0');
                i++;
            }

            i++;
            int col = 0;
            while (i < formula.length() && formula[i] >= '0' && formula[i] <= '9') {
                col = col * 10 + (formula[i] - '0');
                i++;
            }

            double value = 0;
            if (row < data.size() && col < data[row].size()) {
                Formula* formulaCell = dynamic_cast<Formula*>(data[row][col]);
                if (formulaCell != nullptr) {
                    if (!formulaCell->isUpdated) {
                        formulaCell->update(data);
                    }
                }
                value = data[row][col]->getValue();
            }

            operands.push(value);
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