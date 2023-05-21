#pragma once
#include "Cell.h"

class DoubleCell: public Cell {
    double value;

public:
    DoubleCell(std::string str, int row, int col);

    void printToFile(std::ostream& os) const override;
    void print() const override;
    std::string toString() const override;
    Cell* clone() const override;
    double getNumericValue() const override;
};

