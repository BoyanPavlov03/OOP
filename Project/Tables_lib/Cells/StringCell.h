#pragma once
#include <string>
#include "Cell.h"

class StringCell: public Cell {
    /*!
     * The string value of the cell.
     */
    std::string value;

    /*!
     * \brief Extracts the string from the given string.
     * \param str The string to be extracted from.
     * \param row The row of the cell.
     * \param col The column of the cell.
     */
    void extractString(const std::string& str, int row, int col);

public:
    /*!
     * Constructs a string cell from a string.
     * @param originalString The string to be converted to a string cell.
     * @param row The row of the cell.
     * @param col The column of the cell.
     */
    StringCell(const std::string originalString, int row, int col);

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