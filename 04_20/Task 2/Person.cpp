#include <iostream>
#include "Person.h"

Person::Person(const char *name, unsigned int age)
: name(new char[strlen(name) + 1]), age(age) {
    strcpy(this->name, name);
}

Person::Person(const Person &other)
: name(new char[strlen(other.name) + 1]), age(other.age) {
    strcpy(this->name, other.name);
}

