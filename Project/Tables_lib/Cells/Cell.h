#pragma once
#include <string>
#include <iostream>
#include <vector>

class Cell {
protected:
    /*!
     * \brief The original string of the cell.
     */
    std::string originalString;

    /*!
     * \brief The row of the cell.
     */
    int row;

    /*!
     * \brief The column of the cell.
     */
    int col;

    /*!
     * \brief Constructs a cell with the given row and column.
     * \param row The row of the cell.
     * \param col The column of the cell.
     * \param originalString The original string of the cell.
     */
    Cell(int row, int col, std::string originalString = "");

public:
    virtual ~Cell() = default;

    /*!
     * \brief Prints the cell to the given output stream.
     * \param os The output stream to print to.
     */
    virtual void printToFile(std::ostream& os) const = 0;

    /*!
     * \brief Returns the string representation of the cell.
     * \return The string representation of the cell.
     */
    virtual std::string toString() const = 0;

    /*!
     * \brief Returns a copy of the cell.
     * \return A copy of the cell.
     */
    virtual Cell* clone() const = 0;

    /*!
     * \brief Returns the numeric value of the cell.
     * \return The numeric value of the cell.
     */
    virtual double getNumericValue() const = 0;

    /*!
     * \brief Updates the cell.
     * \param data The data of the table.
     */
    virtual void update(const std::vector<std::vector<Cell*>>& data) = 0;

    /*!
     * @param os The output stream to print to.
     * @param cell The cell to print.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Cell& cell);

    /*!
     * \brief Trims the given string from whitespaces.
     * \param str The string to trim.
     * \return The trimmed string.
     */
    static std::string trim(const std::string& str);

    /*!
     * \brief Returns the original string of the cell.
     * \return The original string of the cell.
     */
    std::string getOriginalString() const;
};