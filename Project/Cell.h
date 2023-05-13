#pragma once
#include <string>

class Cell {
public:
    virtual ~Cell() = default;
    virtual void print() const = 0;
    virtual std::string toString() const = 0;
    virtual Cell* clone() const = 0;
    virtual double getValue() const = 0;
};