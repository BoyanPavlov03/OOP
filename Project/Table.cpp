#include "Table.h"
#include "String.h"
#include "Integer.h"
#include "Double.h"
#include "Formula.h"
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

std::string Table::trim(const std::string& str) {
    const auto strBegin = str.find_first_not_of(' ');
    if (strBegin == std::string::npos)
        return "";

    const auto strEnd = str.find_last_not_of(' ');
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

Cell* Table::extractCell(const std::string& str, int row, int col) {
    if (str[0] == '=') {
        return new Formula(0, str);
    } else if (str[0] == '"' && str[str.size() - 1] == '"') {
        return new String(str, row, col);
    } else if (str.find_first_not_of("+-0123456789") == std::string::npos) {
        return new Integer(std::stoi(str));
    } else if (str.find_first_not_of("+-0123456789.") == std::string::npos) {
        double num;
        if (!(std::istringstream(str) >> num >> std::ws).eof()) {
            throw UnknownDataTypeException(str, row, col);
        }
        return new Double(num);
    } else {
        throw UnknownDataTypeException(str, row, col);
    }
}

void Table::updateFormulas() {
    for (auto & row : data) {
        for (auto & cell : row) {
            auto* formula = dynamic_cast<Formula*>(cell);
            if (formula != nullptr && !formula->getIsUpdated()) {
                formula->update(data);
            }
        }
    }
}

void Table::parseCommand(const std::string &command) {
    std::istringstream iss(command);
    std::string commandName;
    iss >> commandName;

    if (!file.is_open() && commandName != "open" && commandName != "help") {
        std::cout << "No file is currently open." << std::endl;
        return;
    }

    if (commandName == "open") {
        iss.ignore();
        std::getline(iss, fileName);
        open();
    } else if (commandName == "close") {
        close();
    } else if (commandName == "save") {
        save(file);
    } else if (commandName == "saveas") {
        std::string newName;
        iss.ignore();
        std::getline(iss, newName);
        saveAs(newName);
    } else if (commandName == "help") {
        help();
    } else if (commandName == "edit") {
        /*
        Edits the value of a cell.
        The cell is given by its coordinates and the new value.
        The value can be a number, a string or a formula.
        If the value is a formula, it is recalculated and the result is saved.
        */
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

    save(newFile);

    newFile.close();
    std::cout << "Successfully saved " << newName << std::endl;
}

void Table::save(std::fstream& fileToSave) {
    for (const auto& row : data) {
        for (const auto& cell : row) {
            fileToSave << cell->toString() << ",";
        }
        fileToSave << std::endl;
    }

    std::cout << "Successfully saved " << fileName << std::endl;
}

void Table::close() {
    if (file.is_open()) {
        file.close();
        data.clear();
        std::cout << "Successfully closed " << fileName << std::endl;
    } else {
        std::cout << "No file is currently open." << std::endl;
    }
}

void Table::open() {
    file = std::fstream(fileName);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << fileName << std::endl;
        return;
    }

    std::string line;
    int rowIndex = 1;
    int colIndex = 1;

    while (std::getline(file, line)) {
        std::string cell;
        std::vector<Cell*> row;

        for (const auto& character : line) {
            if (character == ',') {
                row.push_back(extractCell(trim(cell), rowIndex, colIndex)->clone());
                colIndex++;
                cell = "";
            } else {
                cell += character;
            }
        }

        row.push_back(extractCell(trim(cell), rowIndex, colIndex)->clone());

        data.push_back(row);
        rowIndex++;
        colIndex = 1;
    }

    updateFormulas();
    std::cout << "Successfully opened " << fileName << std::endl;
}

void Table::help() const {
    std::cout << "The following commands are supported:" << std::endl;
    std::cout << "open <file>     opens <file>" << std::endl;
    std::cout << "print           prints the currently opened file" << std::endl;
    std::cout << "edit <coord>    edits the cell at <coord>" << std::endl;
    std::cout << "close           closes currently opened file" << std::endl;
    std::cout << "save            saves the currently open file" << std::endl;
    std::cout << "saveas <file>   saves the currently open file in <file>" << std::endl;
    std::cout << "help            prints this information" << std::endl;
    std::cout << "exit            exists the program" << std::endl;
}

void Table::print() const {
    std::vector<unsigned int> widthsOfEachColumns;
    unsigned int biggestRow = 0;

    for (int i = 0; i < data.size(); i++) {
        if (data[i].size() > biggestRow) {
            biggestRow = data[i].size();
        }

        for (int j = 0; j < data[i].size(); j++) {
            if (widthsOfEachColumns.size() <= j) {
                widthsOfEachColumns.push_back(data[i][j]->toString().size());
            } else if (data[i][j]->toString().size() > widthsOfEachColumns[j]) {
                widthsOfEachColumns[j] = data[i][j]->toString().size();
            }
        }
    }

    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < biggestRow; j++) {
            if (data[i].size() <= j) {
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
