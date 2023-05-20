#include "Table.h"
#include <iostream>

int main() {
    Table* table = new Table();

    while(true) {
        std::string command;
        std::cout << "> ";
        std::getline(std::cin, command);
        if(command == "exit") {
            std::cout << "Exiting the program...;" << std::endl;
            break;
        }
        table->parseCommand(command);
    }

    delete table;
    return 0;
}
