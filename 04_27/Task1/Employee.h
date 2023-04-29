#pragma once
#include <string>

class Employee {
protected:
    std::string name_;
    std::string id_;
    unsigned int experience_{0};
    double salary_{0.0};
public:
    Employee() = default;
    Employee(std::string  name, std::string id, unsigned int experience, double salary);

    const std::string &getName() const;
    const std::string &getId() const;
    unsigned int getExperience() const;
    double getSalary() const;

    void setSalary(double salary);
};
