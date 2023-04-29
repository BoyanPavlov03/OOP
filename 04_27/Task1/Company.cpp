#include "Company.h"
#include <utility>

Company::Company(std::vector<Employee*> employees) :
                 employees_(std::move(employees)) {}

void Company::hireNewEmployee(const Employee& employee) {
    employees_.push_back(new Employee(employee));
}

void Company::fireEmployeeByID(const std::string& id) {
    for (auto it = employees_.begin(); it != employees_.end(); it++) {
        if ((*it)->getId() == id) {
            employees_.erase(it);
            return;
        }
    }
}

double Company::yearlyExpense() {
    double sum = 0.0;
    for(auto employee : employees_) {
        sum += employee->getSalary();
    }
    return sum;
}

void Company::changeSalaryToEmployeeById(const std::string& id, double newSalary) {
    for(auto employee : employees_) {
        if (employee->getId() == id) {
            employee->setSalary(newSalary);
            return;
        }
    }
}


