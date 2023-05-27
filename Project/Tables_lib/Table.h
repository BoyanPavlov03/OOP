#pragma once
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include "Cells/Cell.h"
#include "CommandExecutor.h"

class Table: public CommandExecutor {
private:
    /*!
     * All cells within the table.
     */
    std::vector<std::vector<Cell*>> data;

    /*!
     * Array of the widths for each column.
     */
    std::vector<unsigned int> widthsOfEachColumns;

    /*!
     * Longest row in the table.
     */
    unsigned int biggestRow = 0;

    /*!
     * Loop through all cells and update their formulas and calculate widths for the columns.
     */
    void updateFormulasAndCalculateWidths();

    /*!
     * \brief Updates the cell if it is a formula cell.
     * \param cell The cell to be updated.
     * \param row The row of the cell.
     * \param col The column of the cell.
     */
    void tryToUpdateCell(Cell*& cell, unsigned int row, unsigned int col);

public:
    ~Table();

    void parseCommand(const std::string& command) override;
    void open() override;
    void close() override;
    void save() override;
    void saveAs(const std::string& newName) override;
    void print() const override;
    void help() const override;
    void edit(const std::string cellData, const std::string coordinates) override;

    /*!
     * @param os The output stream.
     * @param table The table to be printed.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Table& table);

    /*!
     * \brief Returns the cell with the given coordinates.
     * \param row The row of the cell.
     * \param col The column of the cell.
     * \return The cell with the given coordinates.
     */
    Cell* getCell(unsigned int row, unsigned int col) const;

    /*!
     * @return Returns the amount of rows in the table.
     */
    unsigned int getRowsCount() const;

    /*!
     * @return Returns the amount of columns in the table.
     */
    unsigned int getColsCount() const;

    /*!
     * \brief Returns the data of the table.
     * \return The data of the table.
     */
    std::vector<std::vector<Cell*>> getData() const;

    /*!
     * \brief Remove all cells from the table.
     */
    void deleteCellsData();

    /*!
     * @param col The column to get the width of.
     * @return Returns the width of the given column.
     */
    unsigned int getColWidth(int col);
};