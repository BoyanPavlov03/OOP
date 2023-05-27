#pragma once
#include "Cell.h"

class ErrorCell: public Cell {
public:
    ErrorCell(int row, int col, const std::string originalString);

    void printToFile(std::ostream& os) const override;
    std::string toString() const override;
    Cell* clone() const override;
    double getNumericValue() const override;
    void update(const std::vector<std::vector<Cell*>>& data) override {}
};