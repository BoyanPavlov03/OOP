#include <fstream>
#include "../ComputerPart.h"
#ifndef COMPUTERPARTWRITER_H_
#define COMPUTERPARTWRITER_H_

class ComputerPartWriter {
    std::ofstream file;

public:
    void write(const ComputerPart &cp, const char* filename);
};

#endif