#include <iostream>

#ifndef COMPUTERPART_H_
#define COMPUTERPART_H_

enum PartType {
    COMPUTER = 0,
    LAPTOP,
    MOUSE,
    KEYBOARD,
    MONITOR,
    HEADPHONES,
    CAMERA
};

class ComputerPart {
    PartType type;
    double price;
    unsigned int warranty;
    char* brand;
    char* model;

public:
    ComputerPart(PartType type, 
                 double price, 
                 unsigned int waranty,
                 const char* brand, 
                 const char* model);
    ComputerPart(const ComputerPart& other);
    ComputerPart& operator=(const ComputerPart& other);
    ~ComputerPart();

    PartType getType() const;
    double getPrice() const;
    const unsigned int getWarranty() const;
    const char* getBrand() const;
    const char* getModel() const;

    void setPrice(double price);

    friend std::ostream &operator<<(std::ostream &os, const ComputerPart &cp);
    friend std::istream &operator>>(std::istream &is, ComputerPart &cp);
};

#endif 