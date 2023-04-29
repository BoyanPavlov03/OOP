#include "Employee.h"
#include <utility>

Employee::Employee(std::string name,
                   std::string id,
                   unsigned int experience,
                   double salary) :
                   name_(std::move(name)),
                   id_(std::move(id)),
                   experience_(experience),
                   salary_(salary) {}

const std::string &Employee::getName() const {
    return name_;
}

const std::string &Employee::getId() const {
    return id_;
}

unsigned int Employee::getExperience() const {
    return experience_;
}

double Employee::getSalary() const {
    return salary_;
}

void Employee::setSalary(double salary) {
    salary_ = salary;
}
