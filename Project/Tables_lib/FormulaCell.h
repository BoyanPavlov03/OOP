#pragma once
#include "Cell.h"
#include <stack>
#include <vector>

class FormulaCell: public Cell {
    double value = 0;
    bool isCurrentlyUpdating = false;

    void calculateTwoNumbers(std::stack<double>& operands, std::stack<char>& operators);

public:
    FormulaCell(const std::string originalString, int row, int col);

    void printToFile(std::ostream& os) const override;
    std::string toString() const override;
    Cell* clone() const override;
    double getNumericValue() const override;
    void update(const std::vector<std::vector<Cell*>>& data) override;
};