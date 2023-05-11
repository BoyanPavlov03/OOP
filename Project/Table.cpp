#include "Table.h"
#include <fstream>
#include <iostream>
#include <string>

Table::Table(const std::string& fileName) {
    readFromFile(fileName);
}

std::string Table::trim(const std::string& str) {
    const auto strBegin = str.find_first_not_of(' ');
    if (strBegin == std::string::npos)
        return "";

    const auto strEnd = str.find_last_not_of(' ');
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

void Table::readFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::string cell;
        for (const auto& character : line) {
            if (character == ',') {
                row.push_back(trim(cell));
                cell = "";
            } else {
                cell += character;
            }
        }

        row.push_back(trim(cell));

        data.push_back(row);
    }
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
                widthsOfEachColumns.push_back(data[i][j].size());
            } else if (data[i][j].size() > widthsOfEachColumns[j]) {
                widthsOfEachColumns.insert(widthsOfEachColumns.begin() + j, data[i][j].size());
            }
        }
    }

    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < biggestRow; j++) {
            if (data[i].size() <= j) {
                std::cout << std::string(widthsOfEachColumns[j] + 2, ' ') << "|";
            } else {
                std::cout << " " << data[i][j] << std::string(widthsOfEachColumns[j] - data[i][j].size(), ' ') << " |";
            }
        }
        std::cout << std::endl;
    }
}


