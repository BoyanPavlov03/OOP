#pragma once
#include <string>
#include <vector>

class CommandExecutor {
protected:
    std::string fileName;
    bool isCurrentlyOpenedFile = false;

public:
    virtual void parseCommand(const std::string& command) = 0;
    virtual ~CommandExecutor() = default;

    virtual void open() = 0;
    virtual void close() = 0;
    virtual void save() = 0;
    virtual void saveAs(const std::string& newName) = 0;
    virtual void print() const = 0;
    virtual void help() const = 0;
    virtual void edit(const std::string cellData, const std::string coordinates) = 0;

    static std::vector<std::string> commands;
};
