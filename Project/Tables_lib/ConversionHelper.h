#pragma once
#include <string>

class ConversionHelper {
public:
    /*!
     * \brief Converts a double to a string.
     * \param number The double to convert.
     * \return The converted string.
     */
    static std::string toString(double number);

    /*!
     * \brief Converts a string to a double.
     * \param string The string to convert.
     * \param row The row of the cell.
     * \param col The column of the cell.
     * \return The converted double.
     */
    static double toDouble(std::string string, unsigned int row, unsigned int col);

    /*!
     * \brief Trims the given string from whitespaces.
     * \param str The string to trim.
     * \return The trimmed string.
     */
    static std::string trim(const std::string& string);
};