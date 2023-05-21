#pragma once
#include "Cell.h"
#include <stack>
#include <vector>

class Formula: public Cell {
    double value = 0;
    bool isUpdated = false;

    void calculateTwoNumbers(std::stack<double>& operands, std::stack<char>& operators);

public:
    Formula(const std::string originalString, int row, int col);

    void printToFile(std::ostream& os) const override;
    void print() const override;
    std::string toString() const override;
    Cell* clone() const override;
    double getNumericValue() const override;

    bool getIsUpdated() const;
    void setIsUpdated(bool isUpdated);
    void update(const std::vector<std::vector<Cell*>>& data);
};