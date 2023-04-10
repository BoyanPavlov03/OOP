#include <iostream>
#include "ComputerPart.h"

ComputerPart::ComputerPart(PartType type, 
                           double price, 
                           unsigned int warranty,
                           const char* brand, 
                           const char* model)
: type(type), 
  price(price), 
  warranty(warranty), 
  brand(new char[strlen(brand) + 1]), 
  model(new char[strlen(model) + 1]) {
    strcpy(this->brand, brand);
    strcpy(this->model, model);
}

ComputerPart::ComputerPart(const ComputerPart& other)
: type(other.type), 
  price(other.price), 
  warranty(other.warranty), 
  brand(new char[strlen(other.brand) + 1]), 
  model(new char[strlen(other.model) + 1]) {
    strcpy(this->brand, other.brand);
    strcpy(this->model, other.model);
}

ComputerPart& ComputerPart::operator=(const ComputerPart& other) {
    if (this != &other) {
        this->type = other.type;
        this->price = other.price;
        delete[] this->brand;
        delete[] this->model;
        this->brand = new char[strlen(other.brand) + 1];
        this->model = new char[strlen(other.model) + 1];
        strcpy(this->brand, other.brand);
        strcpy(this->model, other.model);
    }

    return *this;
}

ComputerPart::~ComputerPart() {
    delete[] this->brand;
    delete[] this->model;
}

PartType ComputerPart::getType() const {
    return this->type;
}

double ComputerPart::getPrice() const {
    return this->price;
}

const unsigned int ComputerPart::getWarranty() const {
    return this->warranty;
}

const char* ComputerPart::getBrand() const {
    return this->brand;
}

const char* ComputerPart::getModel() const {
    return this->model;
}

void ComputerPart::setPrice(double price) {
    if (price > 0) {
        this->price = price;
    }
}

std::ostream &operator<<(std::ostream &os, const ComputerPart &cp) {
    os << "{";

    switch (cp.type) {
    case COMPUTER:
        os << "COMPUTER";
        break;
    case LAPTOP:
        os << "LAPTOP";
        break;
    case MOUSE:
        os << "MOUSE";
        break;
    case KEYBOARD:
        os << "KEYBOARD";
        break;
    case MONITOR:
        os << "MONITOR";
        break;
    case HEADPHONES:
        os << "HEADPHONES";
        break;
    case CAMERA:
        os << "CAMERA";
        break;
    }

    os << "|" << cp.brand
       << "|" << cp.model
       << "|" << cp.warranty
       << "|" << cp.price << "}";

    return os;
}

std::istream &operator>>(std::istream &is, ComputerPart &cp) {
    return is;
}