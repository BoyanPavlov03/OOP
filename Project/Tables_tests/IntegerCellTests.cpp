#include "gtest/gtest.h"
#include "IntegerCell.h"
#include "Exceptions/UnknownDataTypeException.h"

class IntegerCellTests : public ::testing::Test {
protected:
    void SetUp() override {
        integer = new IntegerCell("123", 1, 1);
    }

    void TearDown() override {
        delete integer;
    }

    IntegerCell* integer;
};

TEST_F(IntegerCellTests, constructor) {
    EXPECT_EQ(integer->getNumericValue(), 123);
}

TEST_F(IntegerCellTests, constructorWithInvalidString) {
    try {
        IntegerCell i("abc", 1, 1);
    } catch (UnknownDataTypeException& e) {
        std::string exception = e.what();

        EXPECT_EQ(exception, "Error: row 1, col 1, abc is unknown data type");
    }
}

TEST_F(IntegerCellTests, printToFile) {
    std::stringstream ss;
    integer->printToFile(ss);
    EXPECT_EQ(ss.str(), "123");
}

TEST_F(IntegerCellTests, toString) {
    EXPECT_EQ(integer->toString(), "123");
}

TEST_F(IntegerCellTests, clone) {
    Cell* clone = integer->clone();
    EXPECT_EQ(clone->toString(), "123");
    EXPECT_EQ(clone->getNumericValue(), 123);
    delete clone;
}

TEST_F(IntegerCellTests, getNumericValue) {
    EXPECT_EQ(integer->getNumericValue(), 123);
}
