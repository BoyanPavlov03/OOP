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
    explicit Formula(double value, const std::string formula);
    void print() const override;
    std::string toString() const override;
    Cell* clone() const override;
    double getValue() const override;
    bool getIsUpdated() const;
    void update(const std::vector<std::vector<Cell*>>& data);
};