#include "Programmer.h"
#include <utility>

Programmer::Programmer(std::string name,
                       std::string id,
                       unsigned int experience,
                       double salary,
                       bool knowsCPP,
                       bool knowsJava) :
                       Employee(std::move(name), std::move(id), experience, salary),
                       knowsCPP_(knowsCPP),
                       knowsJava_(knowsJava) {}
