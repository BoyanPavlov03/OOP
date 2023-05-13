#include "Table.h"
#include "String.h"
#include "Integer.h"
#include "Double.h"
#include "UnknownDataTypeException.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

Table::Table(const std::string& fileName) {
    readFromFile(fileName);
}

Table::~Table() {
    for (auto& row : data) {
        for (auto& cell : row) {
            delete &cell;
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

std::string Table::extractString(const std::string& str, int row, int col) {
    std::string result;

    for(int i = 1; i < str.size() - 1; i++) {
        if (str[i] == '\\' && i + 1 < str.size() - 1) {
            if (str[i + 1] == '"') {
                result += '"';
                i++;
            } else if (str[i + 1] == '\\') {
                result += '\\';
                i++;
            } else {
                throw UnknownDataTypeException(str, row, col);
            }
        } else if (str[i] == '\\' && i + 1 >= str.size() - 1) {
            throw UnknownDataTypeException(str, row, col);
        } else {
            result += str[i];
        }
    }

    return result;
}

Cell* Table::extractCell(const std::string& str, int row, int col)  {
    if (str[0] == '"' && str[str.size() - 1] == '"') {
        return new String(extractString(str, row, col));
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

void Table::readFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
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

    file.close();
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


