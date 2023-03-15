#include <iostream>

enum Gender {
    MALE,
    FEMALE
};

class Dog {
    char* name;
    Gender gender;
    int age;
public:
    Dog();
    Dog(const char *name, Gender gender, int age);
    ~Dog();
    void grow();
    char* getName() const;
    Gender getGender();
    int getAge();
    Dog &operator=(const Dog& other);
    friend std::ostream &operator<<(std::ostream &os, const Dog &dog);
};

Dog::Dog() : name(), gender(), age() {}

Dog::Dog(const char *name, Gender gender, int age) : name(new char[strlen(name) + 1]), gender(gender), age(age) {
    strcpy(this->name, name);
}

Dog::~Dog() {
    delete[] name;
}

void Dog::grow() {
    age++;
}

char* Dog::getName() const {
    return name;
}

Gender Dog::getGender() {
    return gender;
}

int Dog::getAge() {
    return age;
}

Dog& Dog::operator=(const Dog& other) {
    if (this != &other) {
        delete[] name;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        gender = other.gender;
        age = other.age;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Dog &dog) {
    os << "Name: " << dog.name << "\n"
       << "Gender: " << dog.gender << "\n"
       << "Age: " << dog.age << "\n";
    return os;
}

class Shelter {
    Dog *dogs;
    int size;
public:
    Shelter();
    ~Shelter();
    Dog *getDogs();
    void addDog(Dog& dog);
    void removeDog(int index);
    friend std::ostream &operator<<(std::ostream &os, const Shelter &shelter);
};

Shelter::Shelter() : dogs(), size() {}

Shelter::~Shelter() {
    delete[] dogs;
}

Dog *Shelter::getDogs() {
    return dogs;
}

void Shelter::addDog(Dog& dog) {
    Dog *newDogs = new Dog[size + 1];
    for (int i = 0; i < size; i++) {
        newDogs[i] = dogs[i];
    }
    newDogs[size] = dog;
    delete[] dogs;
    dogs = newDogs;
    size++;
}

void Shelter::removeDog(int index) {
    Dog *newDogs = new Dog[size - 1];
    for (int i = 0; i < index; i++) {
        newDogs[i] = dogs[i];
    }
    for (int i = index; i < size - 1; i++) {
        newDogs[i] = dogs[i + 1];
    }
    delete[] dogs;
    dogs = newDogs;
    size--;
}

std::ostream &operator<<(std::ostream &os, const Shelter &shelter) {
    for (int i = 0; i < shelter.size; i++) {
        os << shelter.dogs[i];
    }
    return os;
}

int main() {
    Dog dog1("Buddy", MALE, 3);
    Dog dog2("Daisy", FEMALE, 2);
    Dog dog3("Max", MALE, 1);

    Shelter shelter = Shelter();
    shelter.addDog(dog2);
    shelter.addDog(dog3);

    std::cout << "Dogs in the shelter:\n" << shelter;

    shelter.removeDog(1);

    std::cout << "Dogs in the shelter after removing one:\n" << shelter;

    shelter.getDogs()[0].grow();
    std::cout << "New age of " << shelter.getDogs()[0].getName() << ": " << shelter.getDogs()[0].getAge() << "\n";

    return 0;
}
