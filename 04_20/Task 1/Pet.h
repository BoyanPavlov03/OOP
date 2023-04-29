#pragma once

#include "Animal.h" 

class Pet: public Animal {
    char* owner;
    unsigned int telephone;
public:
    explicit Pet(const char* name = "\0", unsigned int age = 0, const char* owner = "\0", unsigned int telephone = 0);
    Pet(const Pet& other);
    Pet& operator=(const Pet& other);
    ~Pet();

    void setOwner(const char *owner);
};