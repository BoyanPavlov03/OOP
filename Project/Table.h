#pragma once
#include <vector>
#include <string>

class Table {
private:
    std::vector<std::vector<std::string>> data;

    std::string trim(const std::string& str);
public:
    Table() = default;
    explicit Table(const std::string& fileName);
    Table(const Table& other) = default;
    Table& operator=(const Table& other) = default;
    ~Table() = default;

    void readFromFile(const std::string& fileName);

    void print() const;

};
