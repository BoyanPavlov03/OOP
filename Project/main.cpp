#include "Table.h"

int main() {
    Table* table = new Table("../table.txt");;
    table->print();

    delete table;
    return 0;
}
