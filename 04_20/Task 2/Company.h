#pragma once
#include "Worker.h"

class Company {
    Worker* workers;
    unsigned int workers_count;
public:
    explicit Company(Worker *workers = nullptr, unsigned int workersCount = 0);
    Company(const Company &other);
    Company& operator=(const Company &other);
};