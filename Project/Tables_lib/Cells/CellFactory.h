#pragma once
#include <string>
#include "Cells/Cell.h"

class CellFactory {
public:
    static Cell* createCell(const std::string& str, int row, int col);
};