#include <iostream>

class Vehicle {
    char* registrationNumber;
    int yearOfManufacture;
    char* brand;
    char* model;
    char* ownerName;

public:

    Vehicle(const char* registrationNumber = "", 
            const int yearOfManufacture = 1970, 
            const char* brand = "", 
            const char* model = "", 
            const char* ownerName = "");
    Vehicle(const Vehicle& other);
    ~Vehicle();
    Vehicle& operator=(const Vehicle& other);
    char* getRegistrationNumber() const;
    int getYearOfManufacture() const;
    char* getBrand() const;
    char* getModel() const;
    char* getOwnerName() const;
    void setRegistrationNumber(char *registrationNumber);
    void setYearOfManufacture(int yearOfManufacture);
    void setBrand(char *brand);
    void setModel(char *model);
    void setOwnerName(char *ownerName);
    bool operator==(const Vehicle& other) const;
};

Vehicle::Vehicle(const char* registrationNumber, 
                 const int yearOfManufacture, 
                 const char* brand, 
                 const char* model, 
                 const char* ownerName) 
    : registrationNumber(new char[strlen(registrationNumber) + 1]), 
      yearOfManufacture(yearOfManufacture), 
      brand(new char[strlen(brand) + 1]), 
      model(new char[strlen(model) + 1]), 
      ownerName(new char[strlen(ownerName) + 1]) {

        strcpy(this->registrationNumber, registrationNumber);
        strcpy(this->brand, brand);
        strcpy(this->model, model);
        strcpy(this->ownerName, ownerName);
}

Vehicle::Vehicle(const Vehicle& other) 
    : registrationNumber(new char[strlen(other.registrationNumber) + 1]), 
      yearOfManufacture(other.yearOfManufacture), 
      brand(new char[strlen(other.brand) + 1]), 
      model(new char[strlen(other.model) + 1]), 
      ownerName(new char[strlen(other.ownerName) + 1]) {

    strcpy(registrationNumber, other.registrationNumber);
    strcpy(brand, other.brand);
    strcpy(model, other.model);
    strcpy(ownerName, other.ownerName);
}

Vehicle& Vehicle::operator=(const Vehicle& other) {
    if (this != &other) {
        delete[] registrationNumber;
        delete[] brand;
        delete[] model;
        delete[] ownerName;
        registrationNumber = new char[strlen(other.registrationNumber) + 1];
        brand = new char[strlen(other.brand) + 1];
        model = new char[strlen(other.model) + 1];
        ownerName = new char[strlen(other.ownerName) + 1];
        strcpy(registrationNumber, other.registrationNumber);
        strcpy(brand, other.brand);
        strcpy(model, other.model);
        strcpy(ownerName, other.ownerName);
        yearOfManufacture = other.yearOfManufacture;
    }
    return *this;
}

Vehicle::~Vehicle() {
    delete[] registrationNumber;
    delete[] brand;
    delete[] model;
    delete[] ownerName;
}

bool Vehicle::operator==(const Vehicle& other) const {
    return yearOfManufacture == other.yearOfManufacture;
}

char* Vehicle::getRegistrationNumber() const {
    return registrationNumber;
}

int Vehicle::getYearOfManufacture() const {
    return yearOfManufacture;
}

char* Vehicle::getBrand() const {
    return brand;
}

char* Vehicle::getModel() const {
    return model;
}

char* Vehicle::getOwnerName() const {
    return ownerName;
}

void Vehicle::setRegistrationNumber(char *registrationNumber) {
    delete[] this->registrationNumber;
    this->registrationNumber = new char[strlen(registrationNumber) + 1];
    strcpy(this->registrationNumber, registrationNumber);
}

void Vehicle::setYearOfManufacture(int yearOfManufacture) {
    this->yearOfManufacture = yearOfManufacture;
}

void Vehicle::setBrand(char *brand) {
    delete[] this->brand;
    this->brand = new char[strlen(brand) + 1];
    strcpy(this->brand, brand);
}

void Vehicle::setModel(char *model) {
    delete[] this->model;
    this->model = new char[strlen(model) + 1];
    strcpy(this->model, model);
}

void Vehicle::setOwnerName(char *ownerName) {
    delete[] this->ownerName;
    this->ownerName = new char[strlen(ownerName) + 1];
    strcpy(this->ownerName, ownerName);
}

int main() {
    Vehicle car1("AB1234CD", 2010, "BMW", "X5", "Ivan Ivanov");

    return 0;
}

