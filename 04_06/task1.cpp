#include <iostream>
#include <fstream>

class Animal {
    char *name;
    char *breed;
    int age;
    char *owner_name;

public:
    Animal(const char* name, const char* breed, const int age, const char* owner_name);
    Animal(const Animal& other);
    ~Animal();
    Animal& operator=(const Animal& other);

    friend std::ostream &operator<<(std::ostream &os, const Animal &animal);
    friend std::istream &operator>>(std::istream &is, Animal &animal);

    void write_to_binary();
    void write_to_text();
};

Animal::Animal(const char* name, const char* breed, const int age, const char* owner_name)
: name(new char[strlen(name) + 1]), 
  breed(new char[strlen(breed) + 1]), 
  age(age), 
  owner_name(new char[strlen(owner_name) + 1]) {
    strcpy(this->name, name);
    strcpy(this->breed, breed);
    strcpy(this->owner_name, owner_name);
}

Animal::Animal(const Animal& other)
: name(new char[strlen(other.name) + 1]), 
  breed(new char[strlen(other.breed) + 1]), 
  age(other.age), 
  owner_name(new char[strlen(other.owner_name) + 1]) {
    strcpy(this->name, other.name);
    strcpy(this->breed, other.breed);
    strcpy(this->owner_name, other.owner_name);
}

Animal::~Animal() {
    delete[] name;
    delete[] breed;
    delete[] owner_name;
}

Animal& Animal::operator=(const Animal& other) {
    if (this != &other) {
        delete[] name;
        delete[] breed;
        delete[] owner_name;

        name = new char[strlen(other.name) + 1];
        breed = new char[strlen(other.breed) + 1];
        owner_name = new char[strlen(other.owner_name) + 1];

        strcpy(this->name, other.name);
        strcpy(this->breed, other.breed);
        strcpy(this->owner_name, other.owner_name);
        this->age = other.age;
    }

    return *this;
}

void Animal::write_to_binary() {
    std::ofstream out("animal.dat", std::ios::binary);

	if (!out) {
		std::cout << "Can't open file!\n";
    } else {

        size_t size_name = strlen(name) + 1;
        out.write((const char*)&size_name, sizeof(size_t));
        out.write(name, size_name);

        size_t size_breed = strlen(breed) + 1;
        out.write((const char*)&size_breed, sizeof(size_t));
        out.write(breed, size_breed);

        out.write((const char*)&age, sizeof(int));

        size_t size_owner_name = strlen(owner_name) + 1;
        out.write((const char*)&size_owner_name, sizeof(size_t));
        out.write(owner_name, size_owner_name);

        out.close();
    }
}

void Animal::write_to_text() {
    std::ofstream outFile;
    outFile.open("animal.txt");
    outFile << *this << std::endl;

    outFile.close();
}

std::ostream &operator<<(std::ostream &os, const Animal &animal) {
    os << animal.name << " / " << animal.breed << " / " << animal.age << " / " << animal.owner_name << "\n";
    return os;
}

std::istream &operator>>(std::istream &is, Animal &animal) {
    is.getline(animal.name, 256);
    is.getline(animal.breed, 256);
    is >> animal.age;
    is.getline(animal.owner_name, 256);
    return is;
}

int main() {
    Animal a("Pesho", "puddle", 5, "Gosho");
    a.write_to_text();
    return 0;
}