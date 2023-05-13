#include "Table.h"
#include <iostream>

int main() {
    Table* table = new Table("../table.txt");;
    table->print();

    delete table;
    return 0;
}
