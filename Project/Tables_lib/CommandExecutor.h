#pragma once
#include <string>
#include <vector>

class CommandExecutor {
protected:
    /*!
     * \brief The name of the file that is currently opened.
     */
    std::string fileName;

    /*!
     * \brief The data of the table.
     */
    bool isCurrentlyOpenedFile = false;

public:
    /*!
     * \brief Constructs a command executor.
     */
    virtual void parseCommand(const std::string& command) = 0;

    /*!
     * \brief Constructs a command executor.
     */
    virtual ~CommandExecutor() = default;

    /*!
     * \brief Opens a file with the given filename.
     */
    virtual void open() = 0;

    /*!
     * \brief Clears all data that was extracted from the file.
     */
    virtual void close() = 0;

    /*!
     * \brief Saves the currently opened file.
     */
    virtual void save() = 0;

    /*!
     * \brief Saves the currently opened file with a new name.
     * \param newName The new name of the file.
     */
    virtual void saveAs(const std::string& newName) = 0;

    /*!
     * \brief Prints the currently opened file.
     */
    virtual void print() const = 0;

    /*!
     * \brief Gives information about the commands.
     */
    virtual void help() const = 0;

    /*!
     * \brief Edit the cell with the given coordinates and data
     * @param cellData The data of the cell.
     * @param coordinates The coordinates of the cell.
     */
    virtual void edit(const std::string cellData, const std::string coordinates) = 0;

    /*!
     * \brief Array of all command names.
     */
    static std::vector<std::string> commands;
};
