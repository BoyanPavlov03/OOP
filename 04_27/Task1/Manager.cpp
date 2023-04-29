#include "Manager.h"

Manager::Manager(std::string name,
                 std::string id,
                 unsigned int experience,
                 double salary,
                 unsigned int managedEmployeesCount) :
                 Employee(std::move(name), std::move(id), experience, salary),
                 managedEmployeesCount_(managedEmployeesCount) {}

