#include <iostream>
#include "Animal.h"

Animal::Animal(const char* name, unsigned int age) : name(new char[strlen(name) + 1]), age(age) {
    strcpy(this->name, name);
}

Animal::Animal(const Animal& other) : name(new char[strlen(other.name) + 1]), age(other.age) {
    strcpy(this->name, other.name);
}

Animal& Animal::operator=(const Animal& other) {
    if (this != &other) {
        delete[] name;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        age = other.age;
    }
    return *this;
}

Animal::~Animal() {
    delete[] name;
}

std::ostream &operator<<(std::ostream &os, const Animal &animal) {
    os << "name: " << animal.name
       << " age: " << animal.age << "\n";
    return os;
}

void Animal::setName(const char *name) {
    Animal::name = name;
}
