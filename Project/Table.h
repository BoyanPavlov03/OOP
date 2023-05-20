#pragma once
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include "Cell.h"
#include "CommandExecutor.h"

class Table: public CommandExecutor {
private:
    std::vector<std::vector<Cell*>> data;

    void updateFormulas();
public:
    Table() = default;
    ~Table();

    void parseCommand(const std::string& command) override;
    void open() override;
    void close() override;
    void save(std::fstream& fileToSave) override;
    void saveAs(const std::string& newName) override;
    void print() const override;
    void help() const override;
};
