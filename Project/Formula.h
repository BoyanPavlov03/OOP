#pragma once
#include "Cell.h"

class Formula: public Cell {
    double value;
    std::string formula;
public:
    explicit Formula(double value, const std::string formula);
    void print() const override;
    std::string toString() const override;
    Cell* clone() const override;
    double getValue() const override;
    void setValue(double value);
    std::string getFormula() const;
};