#include "gtest/gtest.h"
#include "FormulaCell.h"

class FormulaCellTests : public ::testing::Test {};

TEST_F(FormulaCellTests, constructor) {
    try {
        FormulaCell f("=(1 + 3))", 1, 1);
        f.update({});
    } catch (std::invalid_argument& e) {
        std::string exception = e.what();

        EXPECT_EQ(exception, "Invalid formula!");
    }
}

TEST_F(FormulaCellTests, printToFile) {
    FormulaCell f("=(1 + 3)", 1, 1);
    std::stringstream ss;
    f.printToFile(ss);
    EXPECT_EQ(ss.str(), "=(1 + 3)");
}