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
    value = ConversionHelper::round(evaluateRPN(postfix), 4);
}

std::string FormulaCell::infixToPostfix(const std::string& expression, const std::vector<std::vector<Cell*>> &data) {
    std::stack<char> operators;
    std::string postfix;

    // Convert the infix expression to postfix notation
    for (unsigned int index = 1; index < expression.length(); index++) {
        // Skip whitespace characters
        if (expression[index] == ' ') {
            continue;
        }
        // Handle negative numbers or subtraction operator
        else if (expression[index] == '-') {
            // Check if the '-' is part of a negative number or subtraction operator
            if (expression[index + 1] < '0' || expression[index + 1] > '9' && expression[index + 1] != 'R') {
                reOrderOperators(operators, index, expression, postfix);
                continue;
            }

            // Add the '-' symbol to the postfix expression
            postfix += expression[index++];
            // Extract the number following the '-' symbol
            postfix += extractNumber(index, expression);
        }
        // Handle numeric values (including decimals)
        else if (expression[index] >= '0' && expression[index] <= '9' || expression[index] == '.') {
            // Extract the number and add it to the postfix expression
            postfix += extractNumber(index, expression);
        }
        // Handle references to other cells (e.g., 'R1C2')
        else if (expression[index] == 'R') {
            // Get the value of the referenced cell and convert it to a string
            double cellValue = getCellValue(data, index);
            postfix += ConversionHelper::toString(cellValue);
        }
        // Handle operators
        else if (isOperator(expression[index])) {
            reOrderOperators(operators, index, expression, postfix);
        }
        // Handle opening parentheses
        else if (expression[index] == '(') {
            operators.push(expression[index]);
        }
        // Handle closing parentheses
        else if (expression[index] == ')') {
            // Pop operators from the stack and append them to the postfix expression until an opening parenthesis is encountered
            while(!operators.empty() && operators.top() != '(') {
                appendTopOperatorToPostfix(operators, postfix);
            }

            // If the stack is empty before finding an opening parenthesis, it means there is a mismatched parenthesis
            if (operators.empty()) {
                throw InvalidFormulaException(originalString, row, col);
            }
            // Pop the opening parenthesis from the stack
            operators.pop();
        }
        // Handle invalid characters
        else {
            throw InvalidFormulaException(originalString, row, col);
        }
    }

    // Pop any remaining operators from the stack and append them to the postfix expression
    while (!operators.empty()) {
        if (operators.top() == '(') {
            throw InvalidFormulaException(originalString, row, col);
        }

        appendTopOperatorToPostfix(operators, postfix);
    }

    return postfix;
}

double FormulaCell::evaluateRPN(const std::string& expression) {
    std::stack<double> operands;

    // Evaluate the postfix expression using a stack
    for (unsigned int index = 0; index < expression.length(); index++) {
        // Skip whitespace characters
        if (expression[index] == ' ') {
            continue;
        }
        // Handle negative numbers or subtraction operator
        else if (expression[index] == '-') {
            // Check if the '-' is part of a negative number or subtraction operator
            if (expression[index + 1] < '0' || expression[index + 1] > '9') {
                operands.push(performOperation(expression[index], operands));
                continue;
            }
            index++;

            // Extract the number following the '-' symbol
            std::string numberString = extractNumber(index, expression);
            double number = ConversionHelper::toDouble(numberString, row, col);
            // If the '-' is part of a negative number, multiply the number by -1
            if (expression[index - 1] == '-') {
                number *= -1;
            }
            operands.push(number);
        }
        // Handle numeric values (including decimals)
        else if (expression[index] >= '0' && expression[index] <= '9' || expression[index] == '.') {
            // Extract the number and push it to the stack
            std::string numberString = extractNumber(index, expression);
            operands.push(ConversionHelper::toDouble(numberString, row, col));
        }
        // Handle operators
        else if (isOperator(expression[index])) {
            // Perform the operation using the top two operands from the stack and push the result back to the stack
            operands.push(performOperation(expression[index], operands));
        }
    }

    // The final result should be the only remaining value on the stack
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
    // Extract the row number from the cell reference (e.g., 'R1C2')
    while (index < originalString.length() && originalString[index] >= '0' && originalString[index] <= '9') {
        row = row * 10 + (originalString[index] - '0');
        index++;
    }

    index++;
    int col = 0;
    // Extract the column number from the cell reference (e.g., 'R1C2')
    while (index < originalString.length() && originalString[index] >= '0' && originalString[index] <= '9') {
        col = col * 10 + (originalString[index] - '0');
        index++;
    }

    row--;
    col--;

    double cellValue = 0;
    // Check if the referenced cell is within the data range and update it before getting its numeric value
    if (row < data.size() && col < data[row].size()) {
        data[row][col]->update(data);
        cellValue = data[row][col]->getNumericValue();
    }

    return cellValue;
}

std::string FormulaCell::extractNumber(unsigned int &index, const std::string &expression) {
    std::string numberString;
    // Extract the numeric value from the expression
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
    // Get the precedence of the operator
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
    return 0;
}

void FormulaCell::reOrderOperators(std::stack<char> &operators, unsigned int index, const std::string &expression, std::string &postfix) {
    // Reorder the operators based on their precedence and append them to the postfix expression
    while (!operators.empty() &&
           operators.top() != '(' &&
           getPrecedence(expression[index]) <= getPrecedence(operators.top())) {
        appendTopOperatorToPostfix(operators, postfix);
    }

    postfix += ' ';
    operators.push(expression[index]);
}

void FormulaCell::appendTopOperatorToPostfix(std::stack<char> &operators, std::string &postfix) {
    // Append the top operator from the stack to the postfix expression
    postfix += ' ';
    postfix += operators.top();
    operators.pop();
}

double FormulaCell::performOperation(char operation, std::stack<double> &operands) {
    if (operands.size() < 2) {
        throw InvalidFormulaException(originalString, row, col);
    }
    // Perform the specified operation on the top two operands from the stack
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