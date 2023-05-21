#include "Table.h"
#include "StringCell.h"
#include "FormulaCell.h"
#include "CellFactory.h"
#include "UnknownDataTypeException.h"
#include <iostream>
#include <sstream>

Table::~Table() {
    for (auto& row : data) {
        for (auto& cell : row) {
            delete cell;
        }
    }
}

void Table::updateFormulasAndCalculateWidths() {
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            if (data[i][j] == nullptr) {
                continue;
            }

            auto* formula = dynamic_cast<FormulaCell*>(data[i][j]);
            if (formula != nullptr && !formula->getIsUpdated()) {
                formula->update(data);
            }

            if (widthsOfEachColumns.size() <= j) {
                widthsOfEachColumns.push_back(data[i][j]->toString().size());
            } else if (data[i][j]->toString().size() > widthsOfEachColumns[j]) {
                widthsOfEachColumns[j] = data[i][j]->toString().size();
            }
        }
    }
}

void Table::setFormulasAsNotCalculated() {
    for (auto & row : data) {
        for (auto & cell : row) {
            auto* formula = dynamic_cast<FormulaCell*>(cell);
            if (formula != nullptr) {
                formula->setIsUpdated(false);
            }
        }
    }
}

void Table::parseCommand(const std::string &command) {
    std::istringstream iss(command);
    std::string commandName;
    iss >> commandName;

    if (!isCurrentyOpenedFile && commandName != "open" && commandName != "help") {
        std::cout << "No file is currently open." << std::endl;
        return;
    }

    if (commandName == "open") {
        // TODO: Check for quotes
        iss.ignore();
        std::getline(iss, fileName);
        open();
    } else if (commandName == "close") {
        close();
    } else if (commandName == "save") {
        save();
    } else if (commandName == "saveas") {
        std::string newName;
        iss.ignore();
        std::getline(iss, newName);
        saveAs(newName);
    } else if (commandName == "help") {
        help();
    } else if (commandName == "edit") {
        std::string coordinates;
        iss >> coordinates;
        std::string cellData;
        iss.ignore();
        std::getline(iss, cellData);
        edit(Cell::trim(cellData), Cell::trim(coordinates));
    } else if (commandName == "print") {
        print();
    } else {
        std::cout << "Unknown command: " << commandName << std::endl;
    }
}

void Table::saveAs(const std::string &newName) {
    std::fstream newFile(newName);
    if (!newFile.is_open()) {
        std::cout << "Error opening file: " << newName << std::endl;
        return;
    }

    newFile << *this;

    newFile.close();
    std::cout << "Successfully saved " << newName << std::endl;
}

void Table::save() {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Error saving file: " << fileName << std::endl;
        return;
    }
    file << *this;
    file.close();
    std::cout << "Successfully saved " << fileName << std::endl;
}

void Table::close() {
    data.clear();
    fileName = "";
    std::cout << "Successfully closed " << fileName << std::endl;
}

void Table::open() {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << fileName << std::endl;
        return;
    }
    isCurrentyOpenedFile = true;

    std::string line;
    int rowIndex = 1;
    int colIndex = 1;

    while (std::getline(file, line)) {
        std::string lineCell;
        std::vector<Cell*> row;

        for (const auto& character : line) {
            if (character == ',') {
                std::string trimmed = Cell::trim(lineCell);
                if (trimmed.empty()) {
                    row.resize(row.size() + 1);
                    continue;
                }
                Cell* tableCell = CellFactory::createCell(trimmed, rowIndex, colIndex)->clone();
                row.push_back(tableCell);
                colIndex++;

                lineCell = "";
            } else {
                lineCell += character;
            }
        }

        Cell* tableCell = CellFactory::createCell(Cell::trim(lineCell), rowIndex, colIndex)->clone();
        row.push_back(tableCell);

        if (row.size() > biggestRow) {
            biggestRow = row.size();
        }

        data.push_back(row);
        rowIndex++;
        colIndex = 1;
    }

    file.close();

    updateFormulasAndCalculateWidths();
    std::cout << "Successfully opened " << fileName << std::endl;
}

void Table::help() const {
    std::cout << "The following commands are supported:" << std::endl;
    std::cout << "open <file>             opens <file>" << std::endl;
    std::cout << "print                   prints the currently opened file" << std::endl;
    std::cout << "edit <coord> <value>    edits the cell at <coord>" << std::endl;
    std::cout << "close                   closes currently opened file" << std::endl;
    std::cout << "save                    saves the currently open file" << std::endl;
    std::cout << "saveas <file>           saves the currently open file in <file>" << std::endl;
    std::cout << "help                    prints this information" << std::endl;
    std::cout << "exit                    exists the program" << std::endl;
}

void Table::print() const {
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < biggestRow; j++) {
            if (data[i][j] == nullptr || data[i].size() <= j) {
                std::cout << std::string(widthsOfEachColumns[j] + 2, ' ') << "|";
            } else {
                std::cout << " ";
                data[i][j]->print();
                std::cout << std::string(widthsOfEachColumns[j] - data[i][j]->toString().size(), ' ') << " |";
            }
        }
        std::cout << std::endl;
    }
}

void Table::edit(const std::string cellData, const std::string coordinates) {
    int i = 1, row = 0, col = 0;
    while (i < coordinates.length() && coordinates[i] >= '0' && coordinates[i] <= '9') {
        row = row * 10 + (coordinates[i] - '0');
        i++;
    }

    i++;
    while (i < coordinates.length() && coordinates[i] >= '0' && coordinates[i] <= '9') {
        col = col * 10 + (coordinates[i] - '0');
        i++;
    }

    if (row >= data.size()) {
        data.resize(row);
    }

    if (col >= data[row - 1].size()) {
        data[row - 1].resize(col);
    } else {
        delete data[row - 1][col - 1];
    }

    Cell* cell = CellFactory::createCell(cellData, row, col);

    data[row - 1][col - 1] = cell->clone();

    if (data[row - 1].size() > biggestRow) {
        biggestRow = data[row - 1].size();
    }

    setFormulasAsNotCalculated();
    updateFormulasAndCalculateWidths();
    std::cout << "Successfully edited cell " << coordinates << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Table &table) {
    for (const auto& row : table.data) {
        for (const auto& cell : row) {
            if (cell == nullptr) {
                os << ", ";
                continue;
            }

            os << *cell;
            if (cell != row.back()) {
                os << ", ";
            }
        }
        os << std::endl;
    }

    return os;
}

Cell* Table::getCell(unsigned int row, unsigned int col) const {
   if (row >= data.size() || col >= data[row].size()) {
        return nullptr;
    }

    return data[row][col];
}

unsigned int Table::getRowsCount() const {
    return data.size();
}

unsigned int Table::getColsCount() const {
    return biggestRow;
}