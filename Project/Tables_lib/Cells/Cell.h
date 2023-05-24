#pragma once
#include <string>
#include <iostream>
#include <vector>

class Cell {
protected:
    std::string originalString;
    int row;
    int col;
    bool isUpdated = false;

    Cell(int row, int col, std::string originalString = "");

public:
    virtual ~Cell() = default;
    virtual void printToFile(std::ostream& os) const = 0;
    virtual std::string toString() const = 0;
    virtual Cell* clone() const = 0;
    virtual double getNumericValue() const = 0;
    virtual void update(const std::vector<std::vector<Cell*>>& data) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
    static std::string trim(const std::string& str);
    bool getIsUpdated() const;
    void setIsUpdated(bool _isUpdated);
};