#include "Formula.h"
#include <iostream>

Formula::Formula(double value, const std::string formula) : value(value), formula(formula) {}

void Formula::print() const {
    std::cout << value;
}

std::string Formula::toString() const {
    std::string str = std::to_string (value);
    str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
    str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
    return str;
}

Cell *Formula::clone() const {
    return new Formula(*this);
}

double Formula::getValue() const {
    return value;
}

void Formula::setValue(double value) {
    this->value = value;
}

std::string Formula::getFormula() const {
    return formula;
}