#pragma once
#include <string>
#include <iostream>

class Cell {
protected:
    std::string originalString;
    int row;
    int col;

    Cell(int row, int col, std::string originalString = "");

public:
    virtual ~Cell() = default;
    virtual void printToFile(std::ostream& os) const = 0;
    virtual void print() const = 0;
    virtual std::string toString() const = 0;
    virtual Cell* clone() const = 0;
    virtual double getNumericValue() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
    static std::string trim(const std::string& str);
};