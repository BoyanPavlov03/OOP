#pragma once
#include <string>
#include <fstream>

class CommandExecutor {
protected:
    std::fstream file;
    std::string fileName;
public:
    virtual void parseCommand(const std::string& command) = 0;
    virtual ~CommandExecutor() = default;

    virtual void open() = 0;
    virtual void close() = 0;
    virtual void save(std::fstream& fileToSave) = 0;
    virtual void saveAs(const std::string& newName) = 0;
    virtual void print() const = 0;
    virtual void help() const = 0;
};
