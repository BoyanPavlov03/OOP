//
// Created by Boyan Pavlov on 20.04.23.
//

#include "Company.h"

Company::Company(Worker *workers, unsigned int workers_count) : workers(new Worker[workers_count]), workers_count(workers_count) {
    for(int i = 0; i < workers_count; i++) {
        this->workers[i] = workers[i];
    }
}

Company::Company(const Company& other) : workers(new Worker[other.workers_count]), workers_count(other.workers_count) {
    for(int i = 0; i < workers_count; i++) {
        this->workers[i] = workers[i];
    }
}

Company& Company::operator=(const Company &other) {
    if (this != &other) {

    }

    return *this;
}

