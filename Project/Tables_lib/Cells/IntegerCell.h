#pragma once
#include "Cell.h"

class IntegerCell: public Cell {
    /*!
     * The integer value of the cell.
     */
    int value;

public:
    /*!
     * Constructs an integer cell from a string.
     * @param originalString The string to be converted to an integer cell.
     * @param row The row of the cell.
     * @param col The column of the cell.
     */
    IntegerCell(const std::string originalString, int row, int col);

    void printToFile(std::ostream& os) const override;
    std::string toString() const override;
    Cell* clone() const override;
    double getNumericValue() const override;

    /*!
     * \brief Does nothing.
     * \param data The data of the table.
     */
    void update(const std::vector<std::vector<Cell*>>& data) override {}
};