#include "gtest/gtest.h"
#include "IntegerCell.h"
#include "UnknownDataTypeException.h"

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
    EXPECT_THROW(IntegerCell i("abc", 1, 1), UnknownDataTypeException);
}

TEST_F(IntegerCellTests, printToFile) {
    std::stringstream ss;
    integer->printToFile(ss);
    EXPECT_EQ(ss.str(), "123");
}

TEST_F(IntegerCellTests, print) {
    std::stringstream ss;
    testing::internal::CaptureStdout();
    integer->print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "123");
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
