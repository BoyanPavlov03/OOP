#pragma once
#include <string>
#include "Cell.h"

class StringCell: public Cell {
    std::string value;

public:
    StringCell(const std::string originalString, int row, int col);

    void printToFile(std::ostream& os) const override;
    std::string toString() const override;
    Cell* clone() const override;
    double getNumericValue() const override;
    void update(const std::vector<std::vector<Cell*>>& data) override {}

    void extractString(const std::string& str, int row, int col);
};