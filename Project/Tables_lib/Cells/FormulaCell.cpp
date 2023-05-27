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

    for (unsigned int index = 0; index < expression.length(); index++) {
        if (expression[index] == ' ') {
            continue;
        } else if (expression[index] >= '0' && expression[index] <= '9' || expression[index] == '.') {
            postfix += expression[index];
        } else if (expression[index] == 'R') {
            double cellValue = getCellValue(data, index);
            postfix += ConversionHelper::toString(cellValue);
        } else if (isOperator(expression[index])) {
            while (!operators.empty() &&
                   operators.top() != '(' &&
                   getPrecedence(expression[index]) <= getPrecedence(operators.top())) {
                postfix += ' ';
                postfix += operators.top();
                operators.pop();
            }

            postfix += ' ';
            operators.push(expression[index]);
        } else if (expression[index] == '(') {
            operators.push(expression[index]);
        } else if (expression[index] == ')') {
            do {
                if (operators.empty()) {
                    throw InvalidFormulaException(originalString, row, col);
                }

                postfix += ' ';
                postfix += operators.top();
                operators.pop();
            } while(operators.top() != '(');

            operators.pop();
        }
    }

    while (!operators.empty()) {
        postfix += ' ';
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

double FormulaCell::evaluateRPN(const std::string& expression) {
    std::stack<double> operandStack;

    for (unsigned int index = 0; index < expression.length(); index++) {
        if (expression[index] == ' ') {
            continue;
        } else if (expression[index] >= '0' && expression[index] <= '9' || expression[index] == '.') {
            std::string numberString = extractNumber(index, expression);
            operandStack.push(std::stod(numberString));
        } else if (isOperator(expression[index])) {
            if (operandStack.size() < 2) {
                throw InvalidFormulaException(originalString, row, col);
            }

            double operand2 = operandStack.top();
            operandStack.pop();
            double operand1 = operandStack.top();
            operandStack.pop();

            double result = performOperation(expression[index], operand1, operand2);
            operandStack.push(result);
        }
    }

    if (operandStack.size() == 1) {
        isCurrentlyUpdating = false;
        return operandStack.top();
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

double FormulaCell::performOperation(char operation, double operand1, double operand2) {
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
            return pow(operand1, operand2);
        default:
            return 0.0;
    }
}