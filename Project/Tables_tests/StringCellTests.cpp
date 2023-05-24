#include "gtest/gtest.h"
#include "StringCell.h"
#include "Exceptions/UnknownDataTypeException.h"

class StringCellTests : public ::testing::Test {
protected:
    void SetUp() override {
        string = new StringCell("\"abc\"", 1, 1);
    }

    void TearDown() override {
        delete string;
    }

    StringCell* string;
};

TEST_F(StringCellTests, constructor) {
    StringCell s("\"abc\"", 1, 1);
    EXPECT_EQ(s.toString(), "abc");
}

TEST_F(StringCellTests, printToFile) {
    StringCell s("\"abc\"", 1, 1);
    std::stringstream ss;
    s.printToFile(ss);
    EXPECT_EQ(ss.str(), "\"abc\"");
}

TEST_F(StringCellTests, toString) {
    StringCell s("\"abc\"", 1, 1);
    EXPECT_EQ(s.toString(), "abc");
}

TEST_F(StringCellTests, clone) {
    StringCell s("\"abc\"", 1, 1);
    Cell* clone = s.clone();
    EXPECT_EQ(clone->toString(), "abc");
    delete clone;
}

TEST_F(StringCellTests, getNumericValueForString) {
    StringCell s("abc", 1, 1);
    EXPECT_EQ(s.getNumericValue(), 0);
}

TEST_F(StringCellTests, getNumericValueForIntegerWrappedInQuotes) {
    StringCell s("\"123\"", 1, 1);
    EXPECT_EQ(s.getNumericValue(), 123);
}

TEST_F(StringCellTests, extractString) {
    StringCell s("\"abc\"", 1, 1);
    EXPECT_EQ(s.toString(), "abc");
}

TEST_F(StringCellTests, extractStringWithEscapedQuote) {
    StringCell s("\"ab\\\"c\"", 1, 1);
    EXPECT_EQ(s.toString(), "ab\"c");
}

TEST_F(StringCellTests, extractStringWithEscapedBackslash) {
    StringCell s("\"ab\\\\c\"", 1, 1);
    EXPECT_EQ(s.toString(), "ab\\c");
}

TEST_F(StringCellTests, extractStringWithInvalidEscapeSequence) {
    try {
        StringCell s("\"ab\a\\c\"", 1, 1);
    } catch (UnknownDataTypeException& e) {
        std::string exception = e.what();

        EXPECT_EQ(exception, "Error: row 1, col 1, \"ab\a\\c\" is unknown data type");
    }
}