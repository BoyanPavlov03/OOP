#pragma once
#include "Cell.h"

class NullCell: public Cell {
public:
    NullCell(int row, int col) : Cell(row, col) {};

    void printToFile(std::ostream& os) const override { os << ""; }
    std::string toString() const override { return ""; }
    Cell* clone() const override { return new NullCell(*this); }
    double getNumericValue() const override { return 0; };
    void update(const std::vector<std::vector<Cell*>>& data) override {}
};