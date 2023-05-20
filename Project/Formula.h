#pragma once
#include "Cell.h"
#include <stack>
#include <vector>

class Formula: public Cell {
    double value;
    std::string formula;
    bool isUpdated = false;

    void calculateTwoNumbers(std::stack<double>& operands, std::stack<char>& operators);
public:
    Formula(double value, const std::string formula);

    void printToFile(std::ostream& os) const override;
    void print() const override;
    std::string toString() const override;
    Cell* clone() const override;
    double getNumericValue() const override;

    bool getIsUpdated() const;
    std::string getFormula() const;
    void update(const std::vector<std::vector<Cell*>>& data);
};