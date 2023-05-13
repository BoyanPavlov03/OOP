#pragma once
#include <vector>
#include <string>
#include "Cell.h"

class Table {
private:
    std::vector<std::vector<Cell*>> data;

    std::string trim(const std::string& str);
    std::string extractString(const std::string& str);
    Cell* extractCell(const std::string& str);
public:
    Table() = default;
    explicit Table(const std::string& fileName);
    Table(const Table& other) = default;
    Table& operator=(const Table& other) = default;
    ~Table() = default;

    void readFromFile(const std::string& fileName);

    void print() const;
};
