#pragma once

#include <ostream>

class Animal {
protected:
    char* name;
    unsigned int age;
public:
    explicit Animal(const char* name = "\0", unsigned int age = 0);
    Animal(const Animal& other);
    Animal& operator=(const Animal& other);
    ~Animal();

    friend std::ostream &operator<<(std::ostream &os, const Animal &animal);

    void setName(const char *name);
}; 