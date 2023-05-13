#pragma once
#include <string>

class Cell {
public:
    virtual void print() const = 0;
    virtual std::string toString() const = 0;
    virtual Cell* clone() const = 0;
};