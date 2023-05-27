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
    void calculateTwoNumbers(std::stack<double>& operands, std::stack<char>& operators);
    double getCellValue(const std::vector<std::vector<Cell*>>& data, unsigned int& index);
    double extractNumber(std::string number, unsigned int &index);

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
