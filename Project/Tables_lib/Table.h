#pragma once
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include "Cell.h"
#include "CommandExecutor.h"

class Table: public CommandExecutor {
private:
    std::vector<std::vector<Cell*>> data;
    std::vector<unsigned int> widthsOfEachColumns;
    unsigned int biggestRow = 0;

    void updateFormulasAndCalculateWidths();
    void setFormulasAsNotCalculated();

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

    friend std::ostream& operator<<(std::ostream& os, const Table& table);
    Cell* getCell(unsigned int row, unsigned int col) const;
    unsigned int getRowsCount() const;
    unsigned int getColsCount() const;
};