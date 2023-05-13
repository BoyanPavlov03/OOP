#pragma once
#include "Cell.h"

class Integer: public Cell {
    int value;
public:
    explicit Integer(int value);
    void print() const override;
    std::string toString() const override;
    Cell* clone() const override;
};

