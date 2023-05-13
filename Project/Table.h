#pragma once
#include <vector>
#include <string>
#include <stack>
#include "Cell.h"

class Table {
private:
    std::vector<std::vector<Cell*>> data;

    std::string trim(const std::string& str);
    std::string extractString(const std::string& str, int row, int col);
    Cell* extractCell(const std::string& str, int row, int col);
    double calculateFormula(const std::string& formula);
    void calculateTwoNumbers(std::stack<double>& operands, std::stack<char>& operators);
public:
    Table() = default;
    explicit Table(const std::string& fileName);
    ~Table();

    void readFromFile(const std::string& fileName);

    void print() const;
};
