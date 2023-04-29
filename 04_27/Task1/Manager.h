#pragma once
#include "Employee.h"

class Manager: public Employee {
private:
    unsigned int managedEmployeesCount_{0};
public:
    Manager() = default;
    Manager(std::string name, std::string id, unsigned int experience, double salary, unsigned int managedEmployeesCount);
};