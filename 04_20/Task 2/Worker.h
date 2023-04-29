#pragma once
#include "Person.h"

class Worker: public Person {
    double salary;
public:
    explicit Worker(const char *name = "\0", unsigned int age = 0, double salary = 0.0);
};