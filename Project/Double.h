#include "Cell.h"

class Double: public Cell {
    double value;
public:
    explicit Double(double value);
    void print() const override;
    std::string toString() const override;
    Cell* clone() const override;
    double getValue() const override;
};

