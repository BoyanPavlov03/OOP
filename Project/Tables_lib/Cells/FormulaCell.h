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
     * @brief Calculates the value of a cell based on its formula.
     * @param data The table data containing all the cells.
     * @param index The index of the cell in the table data.
     * @return The calculated value of the cell.
     */
    double getCellValue(const std::vector<std::vector<Cell*>>& data, unsigned int& index);

    /*!
     * @brief Extracts a number from the given expression.
     * @param index The current index of the expression.
     * @param expression The expression to extract the number from.
     * @return The extracted number as a string.
     */
    std::string extractNumber(unsigned int &index, const std::string &expression);

    /*!
     * @brief Converts an infix expression to a postfix expression.
     * @param expression The infix expression to convert.
     * @param data The table data containing all the cells.
     * @return The converted postfix expression.
     */
    std::string infixToPostfix(const std::string& expression, const std::vector<std::vector<Cell*>> &data);

    /*!
     * @brief Evaluates a postfix expression and returns the result.
     * @param expression The postfix expression to evaluate.
     * @return The result of the evaluation.
     */
    double evaluateRPN(const std::string& expression);

    /*!
     * @brief Checks if a character is an operator.
     * @param c The character to check.
     * @return `true` if the character is an operator, `false` otherwise.
     */
    bool isOperator(char c);

    /*!
     * @brief Gets the precedence of an operator.
     * @param c The operator to get the precedence of.
     * @return The precedence of the operator.
     */
    int getPrecedence(char c);

    /*!
     * @brief Performs an operation on two operands based on the given operation.
     * @param operation The operation to perform.
     * @param operands The stack of operands.
     * @return The result of the operation.
     */
    double performOperation(char operation, std::stack<double> &operands);

    /*!
     * @brief Reorders the operators in the expression based on precedence and associativity.
     * @param operators The stack of operators.
     * @param index The current index of the expression.
     * @param expression The original infix expression.
     * @param postfix The partially converted postfix expression.
     */
    void reOrderOperators(std::stack<char> &operators, unsigned int index, const std::string &expression, std::string &postfix);

    /*!
     * @brief Appends the top operator from the stack to the postfix expression.
     * @param operators The stack of operators.
     * @param postfix The postfix expression.
     */
    void appendTopOperatorToPostfix(std::stack<char> &operators, std::string &postfix);

public:
    /*!
     * @brief Creates a formula cell from a given string.
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
