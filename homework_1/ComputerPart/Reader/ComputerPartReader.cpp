#include <iostream>
#include <fstream>
#include "../ComputerPart.h"
#include "ComputerPartReader.h"

ComputerPart* ComputerPartReader::read(const char* filename) {
    file = std::ifstream(filename);

    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return nullptr;
    }
    char a = 0;

    while(file >> a) {
        std::cout << a;
    }

    return nullptr;
}