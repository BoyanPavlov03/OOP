#include <iostream>
#include "Pet.h"

Pet::Pet(const char* name, unsigned int age, const char* owner, unsigned int telephone)
: Animal(name, age), owner(new char[strlen(owner) + 1]), telephone(telephone) {
    strcpy(this->owner, owner);
}

Pet::Pet(const Pet& other) : Animal(other), owner(new char[strlen(other.owner) + 1]), telephone(other.telephone) {
    strcpy(this->owner, other.owner);
}

Pet& Pet::operator=(const Pet& other) {
    if (this != &other) {
        Animal::operator=(other);
        delete[] owner;
        owner = new char[strlen(other.owner) + 1];
        strcpy(owner, other.owner);
        telephone = other.telephone;
    }
    return *this;
}

Pet::~Pet() {
    delete[] owner;
}

void Pet::setOwner(const char *owner) {
    Pet::owner = owner;
}
