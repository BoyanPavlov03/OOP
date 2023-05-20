#pragma once
#include <string>
#include <iostream>

class Cell {
public:
    virtual ~Cell() = default;
    virtual void printToFile(std::ostream& os) const = 0;
    virtual void print() const = 0;
    virtual std::string toString() const = 0;
    virtual Cell* clone() const = 0;
    virtual double getNumericValue() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Cell& cell) {
        cell.printToFile(os);
        return os;
    }
};