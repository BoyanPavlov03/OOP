#include <fstream>
#include "../ComputerPart.h"
#ifndef COMPUTERPARTREADER_H_
#define COMPUTERPARTREADER_H_

class ComputerPartReader {
    std::ifstream file;

public:
    ComputerPart* read(const char* filename);
};

#endif