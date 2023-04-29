#pragma once
#include "Employee.h"

class Programmer: public Employee {
private:
    bool knowsCPP_{false};
    bool knowsJava_{false};
public:
    Programmer() = default;
    Programmer(std::string name, std::string id, unsigned int experience, double salary, bool knowsCPP, bool knowsJava);
};