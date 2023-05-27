#pragma once
#include <string>
#include "Cells/Cell.h"

class CellFactory {
public:
    /*!
     * @brief Creates a cell from a string.
     * @param str The string to be converted to a cell.
     * @param row The row of the cell.
     * @param col The column of the cell.
     * @return A pointer to the created cell.
     */
    static Cell* createCell(const std::string& str, int row, int col);
};