#pragma once
#include <string>
#include <exception>

class RecursiveCellException : public std::exception {
    std::string message_;

public:
    RecursiveCellException(const std::string& str, int row, int col)
            : message_("Error: row " + std::to_string(row + 1) + ", col " + std::to_string(col + 1) + ", " + str + " is a recursive formula.") {}

    const char* what() const noexcept override {
        return message_.c_str();
    }
};