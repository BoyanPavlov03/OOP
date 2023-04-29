#include <iostream>
#include "WildAnimal.h"

WildAnimal::WildAnimal(char *name, unsigned int age, Continent continent) : Animal(name, age), continent(continent) {}

std::ostream &operator<<(std::ostream &os, const WildAnimal &animal) {
    os << (const Animal &)(animal) << " continent: " << animal.printContinent();
    return os;
}

const char* WildAnimal::printContinent() const {
    switch (continent) {
        case Continent::EUROPE:
            return "EUROPE";
        case Continent::ANTARCTICA:
            return "ANTARCTICA";
        case Continent::ASIA:
            return "ASIA";
        case Continent::SOUTH_AMERICA:
            return "SOUTH AMERICA";
        case Continent::NORTH_AMERICA:
            return "NORTH AMERICA";
        case Continent::AUSTRALIA:
            return "AUSTRALIA";
        case Continent::AFRICA:
            return "AFRICA";
    }
}

