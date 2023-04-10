#include <iostream>
#include <fstream>
#include "../ComputerPart.h"
#include "ComputerPartWriter.h"

void ComputerPartWriter::write(const ComputerPart &cp, const char* filename) {
    file = std::ofstream(filename);

    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return;
    }

    file << cp << std::endl;
    file.close();
}