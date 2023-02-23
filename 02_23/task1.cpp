#include <iostream>

enum Division {
    ASSASSIN,
    MEDIC,
    MAGE,
    TANK
};

enum Combat {
    UNKNOWN = -1,
    RANGE,
    MELEE,
    BOTH
};

struct Hero {
    char *name;
    Division division;
    Combat combat;
};

void print(Hero *hero) {
    std::cout << "Name: " << hero->name << std::endl;
    std::cout << "Division: " << hero->division << std::endl;
    std::cout << "Combat: " << hero->combat << std::endl;
}

int main() {
    Hero *hero = new Hero();
    hero->name = "Ryoma";
    hero->division = MAGE;
    hero->combat = RANGE;
    print(hero);
    delete hero->name;
    delete hero;
    return 0;
}