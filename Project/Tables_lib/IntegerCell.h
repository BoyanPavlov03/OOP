#pragma once
#include "Cell.h"

class IntegerCell: public Cell {
    int value;

public:
    IntegerCell(const std::string originalString, int row, int col);

    void printToFile(std::ostream& os) const override;
    std::string toString() const override;
    Cell* clone() const override;
    double getNumericValue() const override;
    void update(const std::vector<std::vector<Cell*>>& data) override {}
};