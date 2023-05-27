#pragma once
#include "Cell.h"

class ErrorCell: public Cell {
public:
    /*!
     * @brief Creates an error cell from a string.
     * @param row The row of the cell.
     * @param col The column of the cell.
     * @param originalString The original string of the cell.
     */
    ErrorCell(int row, int col, const std::string originalString);

    /*!
     * \brief Prints the cell's original string to the given output stream.
     * \param os The output stream to print to.
     */
    void printToFile(std::ostream& os) const override;

    /*!
     * \return Returns "ERROR".
     */
    std::string toString() const override;
    Cell* clone() const override;

    /*!
     * \return Returns 0.
     */
    double getNumericValue() const override;

    /*!
     * \brief Does nothing.
     * \param data The data of the table.
     */
    void update(const std::vector<std::vector<Cell*>>& data) override {}
};