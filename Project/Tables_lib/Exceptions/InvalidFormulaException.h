#pragma once
#include <string>
#include <exception>

class InvalidFormulaException : public std::exception {
    std::string message_;

public:
    /*!
     * Constructs an invalid formula exception.
     * @param str The string that caused the exception.
     * @param row The row of the cell.
     * @param col The column of the cell.
     */
    InvalidFormulaException(const std::string& str, int row, int col)
            : message_("Error: row " + std::to_string(row) + ", col " + std::to_string(col) + ", " + str + " is an invalid formula") {}

    const char* what() const noexcept override {
        return message_.c_str();
    }
};
