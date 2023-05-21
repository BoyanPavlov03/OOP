#pragma once
#include <string>
#include "Cell.h"

class CellFactory {
public:
    static Cell* createCell(const std::string& str, int row, int col);
};