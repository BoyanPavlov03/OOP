#include "Table.h"
#include "Cells/StringCell.h"
#include "Cells/CellFactory.h"
#include "Cells/NullCell.h"
#include "Cells/ErrorCell.h"
#include "Exceptions/UnknownDataTypeException.h"
#include "ConversionHelper.h"
#include <iostream>
#include <sstream>
#include <vector>

Table::~Table() {
    deleteCellsData();
}

void Table::updateFormulasAndCalculateWidths() {
    for (int i = 0; i < data.size(); i++) {
        if (data[i].size() < biggestRow) {
            data[i].resize(biggestRow);
        }

        for (int j = 0; j < biggestRow; j++) {
            if (data[i][j] == nullptr) {
                data[i][j] = new NullCell(i + 1, j + 1);
                continue;
            }

            tryToUpdateCell(data[i][j], i + 1, j + 1);

            if (widthsOfEachColumns.size() <= j) {
                widthsOfEachColumns.push_back(data[i][j]->toString().size());
            } else if (data[i][j]->toString().size() > widthsOfEachColumns[j]) {
                widthsOfEachColumns[j] = data[i][j]->toString().size();
            }
        }
    }
}

void Table::tryToUpdateCell(Cell*& cell, unsigned int row, unsigned int col) {
    try {
        cell->update(data);
    } catch (std::exception& e) {
        std::string str = cell->getOriginalString();
        delete cell;
        cell = new ErrorCell(row, col, str);
    }
}

void Table::parseCommand(const std::string &command) {
    std::istringstream iss(command);
    std::string commandName;
    iss >> commandName;

    if (!std::count(CommandExecutor::commands.begin(), CommandExecutor::commands.end(), commandName)) {
        std::cout << "Unknown command: " << commandName << std::endl;
        return;
    }

    if (!isCurrentlyOpenedFile && commandName != "open" && commandName != "help") {
        std::cout << "No file is currently opened." << std::endl;
        return;
    }

    if (commandName == "open") {
        iss.ignore();
        std::getline(iss, fileName);

        std::stringstream ss(fileName);
        std::vector<std::string> words;
        std::string word;
        while (std::getline(ss, word, ' ')) {
            words.push_back(word);
        }

        if (words.size() > 1 && fileName[0] == '\"' && fileName[fileName.size() - 1] == '\"') {
            fileName = fileName.substr(1, fileName.size() - 2);
        } else if (words.size() > 1) {
            std::cout << "Invalid file name." << std::endl;
            return;
        }

        open();
    } else if (commandName == "help") {
        help();
    } else if (commandName == "close") {
        close();
    } else if (commandName == "save") {
        save();
    } else if (commandName == "saveas") {
        std::string newName;
        iss.ignore();
        std::getline(iss, newName);
        saveAs(newName);
    } else if (commandName == "edit") {
        std::string coordinates;
        iss >> coordinates;
        std::string cellData;
        iss.ignore();
        std::getline(iss, cellData);
        edit(ConversionHelper::trim(cellData), ConversionHelper::trim(coordinates));
    } else if (commandName == "print") {
        print();
    }
}

void Table::saveAs(const std::string &newName) {
    std::ofstream newFile(newName);
    if (!newFile.is_open()) {
        std::cout << "Error opening file for save: " << newName << std::endl;
        return;
    }

    newFile << *this;

    newFile.close();
    std::cout << "Successfully saved " << newName << std::endl;
}

void Table::save() {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Error opening file for save: " << fileName << std::endl;
        return;
    }
    file << *this;
    file.close();
    std::cout << "Successfully saved " << fileName << std::endl;
}

void Table::close() {
    deleteCellsData();
    fileName = "";
    isCurrentlyOpenedFile = false;
    std::cout << "Successfully closed " << fileName << std::endl;
}

void Table::open() {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << fileName << std::endl;
        return;
    }
    isCurrentlyOpenedFile = true;

    std::string line;
    int rowIndex = 1;
    int colIndex = 1;

    while (std::getline(file, line)) {
        std::string lineCell;
        std::vector<Cell*> row;

        for (const auto& character : line) {
            if (character == ',') {
                std::string trimmed = ConversionHelper::trim(lineCell);

                Cell* tableCell = CellFactory::createCell(trimmed, rowIndex, colIndex)->clone();
                row.push_back(tableCell);
                colIndex++;

                lineCell = "";
            } else {
                lineCell += character;
            }
        }

        Cell* tableCell = CellFactory::createCell(ConversionHelper::trim(lineCell), rowIndex, colIndex)->clone();
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
    std::cout << "save                    saves the currently opened file" << std::endl;
    std::cout << "saveas <file>           saves the currently opened file in <file>" << std::endl;
    std::cout << "help                    prints this information" << std::endl;
    std::cout << "exit                    exists the program" << std::endl;
}

void Table::print() const {
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < biggestRow; j++) {
            if (dynamic_cast<NullCell*>(data[i][j]) != nullptr || data[i].size() <= j) {
                std::cout << std::string(widthsOfEachColumns[j] + 2, ' ') << "|";
            } else {
                std::cout << " " << data[i][j]->toString()
                          << std::string(widthsOfEachColumns[j] - data[i][j]->toString().size(), ' ')
                          << " |";
            }
        }
        std::cout << std::endl;
    }
}

void Table::edit(const std::string cellData, const std::string coordinates) {
    // Extract row and column values from the coordinates string
    int index = 1, row = 0, col = 0;
    while (index < coordinates.length() && coordinates[index] >= '0' && coordinates[index] <= '9') {
        row = row * 10 + (coordinates[index] - '0');
        index++;
    }

    index++;
    while (index < coordinates.length() && coordinates[index] >= '0' && coordinates[index] <= '9') {
        col = col * 10 + (coordinates[index] - '0');
        index++;
    }

    // Resize the table data if the row is larger than the current size
    if (row >= data.size()) {
        data.resize(row, std::vector<Cell*>());
    }

    // Resize the current row if the column is larger than the current size
    if (col >= data[row - 1].size()) {
        unsigned int currentSize = data[row - 1].size();
        data[row - 1].resize(col);

        // Fill any new cells in the row with NullCell objects
        for (int j = currentSize; j < data[row - 1].size(); j++) {
            data[row - 1][j] = new NullCell(row, j + 1);
        }
    } else {
        // Delete the existing cell at the specified coordinates
        delete data[row - 1][col - 1];
    }

    // Update the biggestRow variable if the current row has more cells than the current maximum
    if (data[row - 1].size() > biggestRow) {
        biggestRow = data[row - 1].size();
    }

    // Create a new cell based on the given cell data and clone it to store in the table data
    Cell* cell = CellFactory::createCell(cellData, row, col);
    data[row - 1][col - 1] = cell->clone();

    // Update the formulas in the table and calculate column widths
    updateFormulasAndCalculateWidths();

    std::cout << "Successfully edited cell " << coordinates << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Table &table) {
    for (const auto& row : table.data) {
        for (const auto& cell : row) {
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
        return new NullCell(row, col);
    }

    return data[row][col];
}

void Table::deleteCellsData() {
    for (auto& row : data) {
        for (auto& cell : row) {
            delete cell;
        }
    }

    data.clear();
    biggestRow = 0;
    widthsOfEachColumns.clear();
}

unsigned int Table::getRowsCount() const {
    return data.size();
}

unsigned int Table::getColsCount() const {
    return biggestRow;
}

std::vector<std::vector<Cell*>> Table::getData() const {
    return data;
}

unsigned int Table::getColWidth(int col) {
    if (col >= widthsOfEachColumns.size()) {
        return 0;
    }

    return widthsOfEachColumns[col];
}

