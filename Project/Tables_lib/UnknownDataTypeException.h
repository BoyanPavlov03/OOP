#pragma once
#include <string>
#include <exception>

class UnknownDataTypeException : public std::exception {
    std::string message_;

public:
    UnknownDataTypeException(const std::string& str, int row, int col)
            : message_("Error: row " + std::to_string(row + 1) + ", col " + std::to_string(col + 1) + ", " + str + " is unknown data type") {}

    const char* what() const noexcept override {
        return message_.c_str();
    }
};