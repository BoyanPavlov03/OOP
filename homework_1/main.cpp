#include <iostream>
#include "ComputerPart/ComputerPart.h"
#include "ComputerPart/Writer/ComputerPartWriter.h"
#include "ComputerPart/Reader/ComputerPartReader.h"

int main() {    
    ComputerPartWriter writer;
    ComputerPartReader reader;

    ComputerPart cp1(MOUSE, 50, 1, "Razer", "Bazilisk");
    ComputerPart cp2(HEADPHONES, 350, 2, "Sony", "XM5");

    writer.write(cp1, "cp1.txt");
    reader.read("cp1.txt");

    return 0;
}