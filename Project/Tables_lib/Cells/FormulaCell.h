#pragma once
#include "Cell.h"
#include <stack>
#include <vector>

class FormulaCell: public Cell {
    /*!
     * @brief The numeric value of the cell.
     */
    double value = 0;

    /*!
     * @brief Used for when we are determining whether recursive cell were to exist.
     */
    bool isCurrentlyUpdating = false;

    /*!
     * @brief Calculates the last 2 operands.
     * @param operands The stack of operands.
     * @param operators The stack of operators.
     */
    double getCellValue(const std::vector<std::vector<Cell*>>& data, unsigned int& index);

    /*!
     * @brief Extracts a number from the expression.
     * @param index The index of the expression.
     * @param expression The expression to extract the number from.
     * @return The extracted number.
     */
    std::string extractNumber(unsigned int &index, const std::string &expression);

    /*!
     * @brief Converts an infix expression to a postfix expression.
     * @param expression The expression to convert.
     * @param data The data of the table.
     * @return The converted expression.
     */
    std::string infixToPostfix(const std::string& expression, const std::vector<std::vector<Cell*>> &data);

    /*!
     * @brief Evaluates a postfix expression.
     * @param expression The expression to evaluate.
     * @return The result of the evaluation.
     */
    double evaluateRPN(const std::string& expression);

    /*!
     * @brief Checks if a character is an operator.
     * @param c The character to check.
     * @return Whether the character is an operator.
     */
    bool isOperator(char c);

    /*!
     * @brief Gets the precedence of an operator.
     * @param c The operator to get the precedence of.
     * @return The precedence of the operator.
     */
    int getPrecedence(char c);

    /*!
     * @brief Performs an operation on 2 operands.
     * @param operation The operation to perform.
     * @param operand1 The first operand.
     * @param operand2 The second operand.
     * @return The result of the operation.
     */
    double performOperation(char operation, std::stack<double> &operands);

    /*!
     * @brief Reorders the operators in the expression.
     * @param operators The stack of operators.
     * @param index The index of the expression.
     * @param expression The expression to reorder.
     * @param postfix The postfix expression.
     */
    void reOrderOperators(std::stack<char> &operators, unsigned int index, const std::string &expression, std::string &postfix);
public:
    /*!
     * @brief Creates a formula cell from a string.
     * @param originalString The string to be converted to a formula cell.
     * @param row The row of the cell.
     * @param col The column of the cell.
     */
    FormulaCell(const std::string originalString, int row, int col);

    void printToFile(std::ostream& os) const override;
    std::string toString() const override;
    Cell* clone() const override;
    double getNumericValue() const override;
    void update(const std::vector<std::vector<Cell*>>& data) override;
};
