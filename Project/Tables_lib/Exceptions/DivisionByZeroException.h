#pragma once
#include <string>
#include <exception>

class DivisionByZeroException : public std::exception {
    std::string message_;

public:
    DivisionByZeroException(const std::string& str, int row, int col)
            : message_("Error: row " + std::to_string(row) + ", col " + std::to_string(col) + ", " + str + " has division by 0") {}

    const char* what() const noexcept override {
        return message_.c_str();
    }
};
