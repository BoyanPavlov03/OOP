#include "gtest/gtest.h"
#include "Table.h"
#include "Cells/IntegerCell.h"
#include "Cells/DoubleCell.h"
#include "Cells/StringCell.h"
#include "Cells/NullCell.h"
#include "Cells/Cell.h"
#include "Exceptions/UnknownDataTypeException.h"
#include "Exceptions/RecursiveCellException.h"
#include <vector>

class TableTests : public ::testing::Test {
protected:
    void SetUp() override {
        table = new Table();
    }

    void TearDown() override {
        delete table;
    }

    Table* table;

    void compareTableCells(const std::vector<std::vector<Cell*>>& expected,
                            const std::vector<std::vector<Cell*>>& actual) {
        EXPECT_EQ(expected.size(), actual.size());
        for (int i = 0; i < actual.size(); i++) {
            for (int j = 0; j < actual[i].size(); j++) {
                EXPECT_EQ(expected[i][j]->toString(), actual[i][j]->toString());
                EXPECT_EQ(expected[i][j]->getNumericValue(), actual[i][j]->getNumericValue());
            }
        }
    }
};

TEST_F(TableTests, constructor) {
    EXPECT_EQ(table->getRowsCount(), 0);
    EXPECT_EQ(table->getColsCount(), 0);
}

TEST_F(TableTests, openCommandWithNoArguments) {
    std::stringstream ss;
    testing::internal::CaptureStdout();
    table->parseCommand("open");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Error opening file: \n");
}

TEST_F(TableTests, openCommandWithTwoArguments) {
    std::stringstream ss;
    testing::internal::CaptureStdout();
    table->parseCommand("open file1.txt file2.txt");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Invalid file name.\n");
}

TEST_F(TableTests, openCommandWithInvalidFileName) {
    std::stringstream ss;
    testing::internal::CaptureStdout();
    table->parseCommand("open fake.txt");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Error opening file: fake.txt\n");
}

TEST_F(TableTests, openCommandWithValidFileName) {
    std::stringstream ss;
    testing::internal::CaptureStdout();
    table->parseCommand("open ../../resources/file1.txt");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Successfully opened ../../resources/file1.txt\n");
}

TEST_F(TableTests, checkTableElements) {
    table->parseCommand("open ../../resources/file1.txt");
    EXPECT_EQ(table->getRowsCount(), 3);
    EXPECT_EQ(table->getColsCount(), 4);

    std::vector<std::vector<Cell*>> data = {
        {
            IntegerCell("10", 1, 1).clone(),
            StringCell("\"Hell\"o world!\\\"", 1, 2).clone(),
            DoubleCell("123.56", 1, 3).clone(),
            NullCell(1, 4).clone()
        },
        {
            StringCell("\"\"Quoted\"\"", 2, 1).clone(),
            IntegerCell("2", 2, 2).clone(),
            NullCell(2, 3).clone(),
            NullCell(2, 4).clone()
        },
        {
            IntegerCell("1", 3, 1).clone(),
            IntegerCell("2", 3, 2).clone(),
            IntegerCell("3", 3, 3).clone(),
            IntegerCell("4", 3, 4).clone()
        }
    };

    compareTableCells(data, table->getData());
}

TEST_F(TableTests, checkTableElementsWithFormulas) {
    table->parseCommand("open ../../resources/file2.txt");
    EXPECT_EQ(table->getRowsCount(), 3);
    EXPECT_EQ(table->getColsCount(), 4);

    std::vector<std::vector<Cell*>> data = {
        {
            IntegerCell("10", 1, 1).clone(),
            StringCell("\"Hello world!\"", 1, 2).clone(),
            DoubleCell("123.56", 1, 3).clone(),
            NullCell(1, 4).clone()
        },
        {
            StringCell("\"\"Quoted\"\"", 2, 1).clone(),
            NullCell(2, 2).clone(),
            DoubleCell("4", 2, 3).clone(),
            NullCell(2, 4).clone()
        },
        {
            IntegerCell("1", 3, 1).clone(),
            IntegerCell("2", 3, 2).clone(),
            IntegerCell("3", 3, 3).clone(),
            IntegerCell("4", 3, 4).clone()
        }
    };

    compareTableCells(data, table->getData());
}

TEST_F(TableTests, checkTableElementsAfterEdit) {
    table->parseCommand("open ../../resources/file2.txt");
    EXPECT_EQ(table->getRowsCount(), 3);
    EXPECT_EQ(table->getColsCount(), 4);

    std::vector<std::vector<Cell*>> data = {
        {
            IntegerCell("10", 1, 1).clone(),
            StringCell("\"Hello world!\"", 1, 2).clone(),
            DoubleCell("123.56", 1, 3).clone(),
            NullCell(1, 4).clone(),
            NullCell(1, 5).clone()
        },
        {
            StringCell("\"\"Quoted\"\"", 2, 1).clone(),
            NullCell(2, 2).clone(),
            DoubleCell("4", 2, 3).clone(),
            NullCell(2, 4).clone(),
            NullCell(2, 5).clone()
        },
        {
            IntegerCell("1", 3, 1).clone(),
            IntegerCell("2", 3, 2).clone(),
            IntegerCell("3", 3, 3).clone(),
            IntegerCell("4", 3, 4).clone(),
            NullCell(3, 5).clone()
        },
        {
            NullCell(4, 1).clone(),
            NullCell(4, 2).clone(),
            NullCell(4, 3).clone(),
            NullCell(4, 4).clone(),
            NullCell(4, 5).clone()
        },
        {
            NullCell(5, 1).clone(),
            NullCell(5, 2).clone(),
            NullCell(5, 3).clone(),
            NullCell(5, 4).clone(),
            IntegerCell("15", 5, 5).clone()
        }
    };

    table->parseCommand("edit R5C5 15");

    compareTableCells(data, table->getData());
}

TEST_F(TableTests, invalidStringPassedToTheTable) {
    try {
        table->parseCommand("open ../../resources/file3.txt");
    } catch (UnknownDataTypeException& e) {
        std::string exceptionMessage = e.what();

        EXPECT_EQ(exceptionMessage, "Error: row 1, col 2, Hello is unknown data type");
    }
}

TEST_F(TableTests, tryingToUseOtherCommandsBeforeOpeningFile) {
    std::stringstream ss;
    testing::internal::CaptureStdout();
    table->parseCommand("edit R1C1 15");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "No file is currently opened.\n");
}

TEST_F(TableTests, checkCorrectWidthCalculation) {
    table->parseCommand("open ../../resources/file1.txt");
    EXPECT_EQ(table->getColsCount(), 4);
    EXPECT_EQ(table->getColWidth(0), 8);
    EXPECT_EQ(table->getColWidth(1), 14);
    EXPECT_EQ(table->getColWidth(2), 6);
    EXPECT_EQ(table->getColWidth(3), 1);
}

TEST_F(TableTests, usePrintCommandAfterOpeningFile) {
    table->parseCommand("open ../../resources/file1.txt");
    std::stringstream ss;
    testing::internal::CaptureStdout();
    table->parseCommand("print");
    std::string output = testing::internal::GetCapturedStdout();
    std::string expectedOutput = " 10       | Hell\"o world!\\ | 123.56 |   |\n"
                                 " \"Quoted\" | 2              |        |   |\n"
                                 " 1        | 2              | 3      | 4 |\n";
    EXPECT_EQ(output, expectedOutput);
}

TEST_F(TableTests, openFileWithSpaceInNameWithoutQuotes) {
    std::stringstream ss;
    testing::internal::CaptureStdout();
    table->parseCommand("open ../../resources/file 4.txt");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Invalid file name.\n");
}

TEST_F(TableTests, openFIleWithSpaceInNameWithQuotes) {
    table->parseCommand("open \"../../resources/file 4.txt\"");

    std::vector<std::vector<Cell*>> data = {
        {
            IntegerCell("1", 1, 1).clone(),
            IntegerCell("2", 1, 2).clone(),
            IntegerCell("3", 1, 3).clone(),
            IntegerCell("4", 1, 4).clone()
        },
        {
            StringCell("\"Hi\"", 2, 1).clone(),
            NullCell(2, 2).clone(),
            DoubleCell("3", 2, 3).clone(),
            NullCell(2, 4).clone()
        },
    };

    compareTableCells(data, table->getData());
}

TEST_F(TableTests, accessCellThatIsOutOfBounds) {
    table->parseCommand("open ../../resources/file1.txt");
    Cell* cell = table->getCell(5,5);
    EXPECT_TRUE(dynamic_cast<NullCell*>(cell) != nullptr);
}

TEST_F(TableTests, closeFile) {
    table->parseCommand("open ../../resources/file1.txt");
    table->parseCommand("close");
    EXPECT_TRUE(table->getData().empty());
    EXPECT_TRUE(table->getColsCount() == 0);
    EXPECT_TRUE(table->getRowsCount() == 0);
    std::stringstream ss;
    testing::internal::CaptureStdout();
    table->parseCommand("print");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "No file is currently opened.\n");
}

TEST_F(TableTests, saveFile) {
    table->parseCommand("open ../../resources/file1.txt");
    int valueAtR1C1 = table->getCell(0,0)->getNumericValue() + 5;
    table->parseCommand("edit R1C1 " + std::to_string(valueAtR1C1));
    table->parseCommand("save");
    table->parseCommand("close");
    table->parseCommand("open ../../resources/file1.txt");

    std::vector<std::vector<Cell*>> data = {
        {
            IntegerCell(std::to_string(valueAtR1C1), 1, 1).clone(),
            StringCell("\"Hell\"o world!\\\"", 1, 2).clone(),
            DoubleCell("123.56", 1, 3).clone(),
            NullCell(1, 4).clone()
        },
        {
            StringCell("\"\"Quoted\"\"", 2, 1).clone(),
            IntegerCell("2", 2, 2).clone(),
            NullCell(2, 3).clone(),
            NullCell(2, 4).clone()
        },
        {
            IntegerCell("1", 3, 1).clone(),
            IntegerCell("2", 3, 2).clone(),
            IntegerCell("3", 3, 3).clone(),
            IntegerCell("4", 3, 4).clone()
        }
    };

    compareTableCells(data, table->getData());

    table->parseCommand("edit R1C1 " + std::to_string(valueAtR1C1 - 5));
    table->parseCommand("save");
}

TEST_F(TableTests, saveAsCommand) {
    table->parseCommand("open ../../resources/file1.txt");
    int valueAtR1C1 = table->getCell(0,0)->getNumericValue() + 5;
    table->parseCommand("edit R1C1 " + std::to_string(valueAtR1C1));
    table->parseCommand("saveas ../../resources/file5.txt");
    table->parseCommand("close");
    table->parseCommand("open ../../resources/file5.txt");

    std::vector<std::vector<Cell*>> data = {
        {
            IntegerCell(std::to_string(valueAtR1C1), 1, 1).clone(),
            StringCell("\"Hell\"o world!\\\"", 1, 2).clone(),
            DoubleCell("123.56", 1, 3).clone(),
            NullCell(1, 4).clone()
        },
        {
            StringCell("\"\"Quoted\"\"", 2, 1).clone(),
            IntegerCell("2", 2, 2).clone(),
            NullCell(2, 3).clone(),
            NullCell(2, 4).clone()
        },
        {
            IntegerCell("1", 3, 1).clone(),
            IntegerCell("2", 3, 2).clone(),
            IntegerCell("3", 3, 3).clone(),
            IntegerCell("4", 3, 4).clone()
        }
    };

    compareTableCells(data, table->getData());
    table->deleteCellsData();
    table->parseCommand("save");
}

TEST_F(TableTests, helpCommand) {
    std::stringstream ss;
    testing::internal::CaptureStdout();
    table->parseCommand("help");
    std::string output = testing::internal::GetCapturedStdout();
    std::string expectedOutput = "The following commands are supported:\n"
                                 "open <file>             opens <file>\n"
                                 "print                   prints the currently opened file\n"
                                 "edit <coord> <value>    edits the cell at <coord>\n"
                                 "close                   closes currently opened file\n"
                                 "save                    saves the currently opened file\n"
                                 "saveas <file>           saves the currently opened file in <file>\n"
                                 "help                    prints this information\n"
                                 "exit                    exists the program\n";
    EXPECT_EQ(output, expectedOutput);
}

TEST_F(TableTests, testColWidthWhenOutOfRange) {
    table->parseCommand("open ../../resources/file1.txt");
    EXPECT_EQ(table->getColWidth(5), 0);
}

TEST_F(TableTests, testColWidthWhenInRange) {
    table->parseCommand("open ../../resources/file1.txt");
    EXPECT_EQ(table->getColWidth(1), 14);
}

TEST_F(TableTests, unknownCommand) {
    std::stringstream ss;
    testing::internal::CaptureStdout();
    table->parseCommand("random");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Unknown command: random\n");
}

TEST_F(TableTests, recursiveFormulas) {
    try {
        table->parseCommand("open ../../resources/file6.txt");
    } catch (RecursiveCellException& e) {
        std::string exceptionMessage = e.what();

        EXPECT_EQ(exceptionMessage, "Error: row 1, col 3, =R2C2 is a recursive formula");
    }
}

TEST_F(TableTests, testSaveWhenFileOpeningFails) {
    table->parseCommand("open ../../resources/readOnlyFile.txt");
    std::stringstream ss;
    testing::internal::CaptureStdout();
    table->parseCommand("save");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Error opening file for save: ../../resources/readOnlyFile.txt\n");
}

TEST_F(TableTests, testSaveAsWhenFileOpeningFails) {
    table->parseCommand("open ../../resources/file1.txt");
    std::stringstream ss;
    testing::internal::CaptureStdout();
    table->parseCommand("saveas ../../resources/readOnlyFile.txt");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Error opening file for save: ../../resources/readOnlyFile.txt\n");
}