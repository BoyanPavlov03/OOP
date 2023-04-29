#pragma once
#include <vector>
#include "Employee.h"

class Company {
private:
    std::vector<Employee*> employees_;
public:
    Company() = default;
    explicit Company(std::vector<Employee*> employees);

    void hireNewEmployee(const Employee& employee);
    void fireEmployeeByID(const std::string& id);
    double yearlyExpense();
    void changeSalaryToEmployeeById(const std::string& id, double newSalary);
};