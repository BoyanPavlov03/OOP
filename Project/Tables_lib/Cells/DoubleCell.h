#pragma once
#include "Cell.h"

class DoubleCell: public Cell {
    /*!
     * @brief The decimal value of the cell.
     */
    double value;

public:
    /*!
     * @brief Creates a double cell from a string.
     * @param str The string to be converted to a double cell.
     * @param row The row of the cell.
     * @param col The column of the cell.
     */
    DoubleCell(std::string str, int row, int col);

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

