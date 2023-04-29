#pragma once

#include <ostream>
#include "Animal.h"

enum class Continent {
    EUROPE,
    AFRICA,
    ASIA,
    SOUTH_AMERICA,
    NORTH_AMERICA,
    ANTARCTICA,
    AUSTRALIA
};

class WildAnimal: public Animal {
    Continent continent;
public:
    WildAnimal(char *name, unsigned int age, Continent continent);

    friend std::ostream &operator<<(std::ostream &os, const WildAnimal &animal);
    const char* printContinent() const;

};