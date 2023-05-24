#pragma once
#include <string>
#include <exception>

class InvalidFormulaException : public std::exception {
    std::string message_;

public:
    InvalidFormulaException(const std::string& str, int row, int col)
            : message_("Error: row " + std::to_string(row) + ", col " + std::to_string(col) + ", " + str + " is an invalid formula") {}

    const char* what() const noexcept override {
        return message_.c_str();
    }
};
