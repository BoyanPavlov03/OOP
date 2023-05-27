#include "FormulaCell.h"
#include "Exceptions/RecursiveCellException.h"
#include "Exceptions/InvalidFormulaException.h"
#include "Exceptions/DivisionByZeroException.h"
#include "ConversionHelper.h"
#include <iostream>
#include <cmath>

FormulaCell::FormulaCell(const std::string originalString, int row, int col) : Cell(row, col, originalString) {}

void FormulaCell::printToFile(std::ostream& os) const {
    os << originalString;
}

std::string FormulaCell::toString() const {
    return ConversionHelper::toString(value);
}

Cell *FormulaCell::clone() const {
    return new FormulaCell(*this);
}

double FormulaCell::getNumericValue() const {
    return value;
}

void FormulaCell::update(const std::vector<std::vector<Cell*>> &data) {
    if (isCurrentlyUpdating) {
        throw RecursiveCellException(originalString, row, col);
    }
    isCurrentlyUpdating = true;

    std::string postfix = infixToPostfix(originalString, data);
    value = evaluateRPN(postfix);
}

std::string FormulaCell::infixToPostfix(const std::string& expression, const std::vector<std::vector<Cell*>> &data) {
    std::stack<char> operators;
    std::string postfix;

    for (unsigned int index = 1; index < expression.length(); index++) {
        if (expression[index] == ' ') {
            continue;
        } else if (expression[index] == '-') {
            if (expression[index + 1] < '0' || expression[index + 1] > '9' && expression[index + 1] != 'R') {
                reOrderOperators(operators, index, expression, postfix);
                continue;
            }

            postfix += expression[index++];
            postfix += extractNumber(index, expression);
        } else if (expression[index] >= '0' && expression[index] <= '9' || expression[index] == '.') {
            postfix += extractNumber(index, expression);
        } else if (expression[index] == 'R') {
            double cellValue = getCellValue(data, index);
            postfix += ConversionHelper::toString(cellValue);
        } else if (isOperator(expression[index])) {
            reOrderOperators(operators, index, expression, postfix);
        } else if (expression[index] == '(') {
            operators.push(expression[index]);
        } else if (expression[index] == ')') {
            while(!operators.empty() && operators.top() != '(') {
                postfix += ' ';
                postfix += operators.top();
                operators.pop();
            }

            if (operators.empty()) {
                throw InvalidFormulaException(originalString, row, col);
            }
            operators.pop();
        } else {
            throw InvalidFormulaException(originalString, row, col);
        }
    }

    while (!operators.empty()) {
        if (operators.top() == '(') {
            throw InvalidFormulaException(originalString, row, col);
        }

        postfix += ' ';
        postfix += operators.top();
        operators.pop();
    }

    std::cout << postfix << std::endl;

    return postfix;
}

double FormulaCell::evaluateRPN(const std::string& expression) {
    std::stack<double> operands;

    for (unsigned int index = 0; index < expression.length(); index++) {

        if (expression[index] == ' ') {
            continue;
        } else if (expression[index] == '-') {
            if (expression[index + 1] < '0' || expression[index + 1] > '9') {
                operands.push(performOperation(expression[index], operands));
                continue;
            }
            index++;

            std::string numberString = extractNumber(index, expression);
            double number = std::stod(numberString);
            if (expression[index - 1] == '-') {
                number *= -1;
            }
            operands.push(number);
        } else if (expression[index] >= '0' && expression[index] <= '9' || expression[index] == '.') {
            std::string numberString = extractNumber(index, expression);
            operands.push(std::stod(numberString));
        } else if (isOperator(expression[index])) {
            operands.push(performOperation(expression[index], operands));
        }
    }

    if (operands.size() == 1) {
        isCurrentlyUpdating = false;
        return operands.top();
    } else {
        throw InvalidFormulaException(originalString, row, col);
    }
}

double FormulaCell::getCellValue(const std::vector<std::vector<Cell*>> &data, unsigned int &index) {
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
        data[row][col]->update(data);
        cellValue = data[row][col]->getNumericValue();
    }

    return cellValue;
}

std::string FormulaCell::extractNumber(unsigned int &index, const std::string &expression) {
    std::string numberString;
    while (expression[index] >= '0' && expression[index] <= '9' || expression[index] == '.') {
        numberString += expression[index];
        index++;
    }

    index--;
    return numberString;
}

bool FormulaCell::isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int FormulaCell::getPrecedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
    return 0;
}

void FormulaCell::reOrderOperators(std::stack<char> &operators, unsigned int index, const std::string &expression, std::string &postfix) {
    while (!operators.empty() &&
           operators.top() != '(' &&
           getPrecedence(expression[index]) <= getPrecedence(operators.top())) {
        postfix += ' ';
        postfix += operators.top();
        operators.pop();
    }

    postfix += ' ';
    operators.push(expression[index]);
}

double FormulaCell::performOperation(char operation, std::stack<double> &operands) {
    if (operands.size() < 2) {
        throw InvalidFormulaException(originalString, row, col);
    }
    double operand2 = operands.top();
    operands.pop();
    double operand1 = operands.top();
    operands.pop();

    switch (operation) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 == 0) {
                throw DivisionByZeroException(originalString, row, col);
            }
            return operand1 / operand2;
        case '^':
            if (operand1 < 0) {
                return pow(operand1, operand2) * -1;
            }
            return pow(operand1, operand2);
        default:
            return 0.0;
    }
}