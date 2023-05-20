#pragma once
#include "Cell.h"

class Integer: public Cell {
    int value;
public:
    explicit Integer(int value);
    void printToFile(std::ostream& os) const override;
    void print() const override;
    std::string toString() const override;
    Cell* clone() const override;
    double getNumericValue() const override;
};

