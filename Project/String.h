#pragma once
#include <string>
#include "Cell.h"

class String: public Cell {
    std::string value;
public:
    explicit String(const std::string value);
    void print() const override;
    std::string toString() const override;
};

