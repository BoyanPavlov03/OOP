#pragma once
#include <string>

class Ticket {
private:
    std::string showName;
    double price;


public:
    explicit Ticket(const std::string &showName = "", double price = 0.0);

};
