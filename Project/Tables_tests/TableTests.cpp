#include "gtest/gtest.h"
#include "Table.h"
#include <unistd.h>

class TableTests : public ::testing::Test {
protected:
    void SetUp() override {
        table = new Table();
    }

    void TearDown() override {
        delete table;
    }

    Table* table;
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
    Table table;
    std::stringstream ss;
    testing::internal::CaptureStdout();
    table.parseCommand("open file1.txt file2.txt");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Error opening file: file1.txt file2.txt\n");
}

TEST_F(TableTests, openCommandWithInvalidFileName) {
    Table table;
    std::stringstream ss;
    testing::internal::CaptureStdout();
    table.parseCommand("open fake.txt");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Error opening file: fake.txt\n");
}

TEST_F(TableTests, openCommandWithValidFileName) {
    Table table;
    std::stringstream ss;
    testing::internal::CaptureStdout();
    table.parseCommand("open ../../Tables_tests/file1.txt");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Successfully opened ../../Tables_tests/file1.txt\n");
}