#include "gtest/gtest.h"
#include "DoubleCell.h"
#include "Exceptions/UnknownDataTypeException.h"

class DoubleCellTests : public ::testing::Test {};

TEST_F(DoubleCellTests, constructor) {
    try {
        DoubleCell d("123.456.13", 1, 1);
    } catch (UnknownDataTypeException& e) {
        std::string exception = e.what();

        EXPECT_EQ(exception, "Error: row 1, col 1, 123.456.13 is unknown data type");
    }
}