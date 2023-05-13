#pragma once
#include <vector>
#include <string>
#include "Cell.h"

class Table {
private:
    std::vector<std::vector<Cell*>> data;

    std::string trim(const std::string& str);
    std::string extractString(const std::string& str, int row, int col);
    Cell* extractCell(const std::string& str, int row, int col);
    double calculateFormula(const std::string& formula);
public:
    Table() = default;
    explicit Table(const std::string& fileName);
    ~Table();

    void readFromFile(const std::string& fileName);

    void print() const;
};
